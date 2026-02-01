/*
 * Aether Command - Modern Terminal Emulator
 * Copyright (C) 2026 NurOS
 * Developer: AnmiTaliDev
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

namespace AetherCommand {
    public class Terminal : Gtk.Box {
        private Vte.Terminal vte_terminal;

        public signal void title_changed (string title);

        public Terminal () {
            Object (
                orientation: Gtk.Orientation.VERTICAL,
                spacing: 0
            );

            setup_terminal ();
        }

        private void setup_terminal () {
            vte_terminal = new Vte.Terminal ();
            vte_terminal.hexpand = true;
            vte_terminal.vexpand = true;

            vte_terminal.notify["window-title"].connect (() => {
                GLib.Value val = GLib.Value (typeof (string));
                vte_terminal.get_property ("window-title", ref val);
                string? new_title = val.get_string ();

                if (new_title != null && new_title != "") {
                    title_changed (new_title);
                }
            });

            setup_shortcuts ();
            setup_context_menu ();

            vte_terminal.spawn_async (
                Vte.PtyFlags.DEFAULT,
                Environment.get_home_dir (),
                { Environment.get_variable ("SHELL") ?? "/bin/bash" },
                null,
                GLib.SpawnFlags.SEARCH_PATH,
                null,
                -1,
                null,
                null
            );

            append (vte_terminal);
        }

        private void setup_shortcuts () {
            var key_controller = new Gtk.EventControllerKey ();

            key_controller.key_pressed.connect ((keyval, keycode, state) => {
                if ((state & Gdk.ModifierType.CONTROL_MASK) != 0 &&
                    (state & Gdk.ModifierType.SHIFT_MASK) != 0) {

                    if (keyval == Gdk.Key.C || keyval == Gdk.Key.c) {
                        vte_terminal.copy_clipboard_format (Vte.Format.TEXT);
                        return true;
                    }

                    if (keyval == Gdk.Key.V || keyval == Gdk.Key.v) {
                        vte_terminal.paste_clipboard ();
                        return true;
                    }
                }

                return false;
            });

            vte_terminal.add_controller (key_controller);
        }

        private void setup_context_menu () {
            var menu = new GLib.Menu ();

            var copy_item = new GLib.MenuItem ("Copy", "term.copy");
            menu.append_item (copy_item);

            var paste_item = new GLib.MenuItem ("Paste", "term.paste");
            menu.append_item (paste_item);

            var popover = new Gtk.PopoverMenu.from_model (menu);
            popover.set_parent (vte_terminal);
            popover.has_arrow = false;

            var gesture = new Gtk.GestureClick ();
            gesture.set_button (3); // Right click

            gesture.pressed.connect ((n_press, x, y) => {
                var rect = Gdk.Rectangle () {
                    x = (int) x,
                    y = (int) y,
                    width = 1,
                    height = 1
                };
                popover.set_pointing_to (rect);
                popover.popup ();
            });

            vte_terminal.add_controller (gesture);

            var action_group = new GLib.SimpleActionGroup ();

            var copy_action = new GLib.SimpleAction ("copy", null);
            copy_action.activate.connect (() => {
                vte_terminal.copy_clipboard_format (Vte.Format.TEXT);
            });
            action_group.add_action (copy_action);

            var paste_action = new GLib.SimpleAction ("paste", null);
            paste_action.activate.connect (() => {
                vte_terminal.paste_clipboard ();
            });
            action_group.add_action (paste_action);

            vte_terminal.insert_action_group ("term", action_group);
        }
    }
}
