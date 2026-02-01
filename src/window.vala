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
    [GtkTemplate (ui = "/org/aether/command/window.ui")]
    public class MainWindow : Adw.ApplicationWindow {
        [GtkChild]
        private unowned Adw.TabView tab_view;

        [GtkChild]
        private unowned Adw.WindowTitle window_title;

        [GtkChild]
        private unowned Gtk.Button new_tab_button;

        public MainWindow (Gtk.Application app) {
            Object (application: app);

            setup_window ();
            setup_tabs ();
            add_new_tab ();
        }

        private void setup_window () {
            icon_name = "utilities-terminal";
            default_width = 800;
            default_height = 600;
        }

        private void setup_tabs () {
            new_tab_button.clicked.connect (() => {
                add_new_tab ();
            });

            tab_view.notify["selected-page"].connect (() => {
                update_title ();
            });

            tab_view.close_page.connect ((page) => {
                if (tab_view.get_n_pages () == 1) {
                    close ();
                    return true;
                }
                return false;
            });
        }

        private void add_new_tab () {
            var terminal = new Terminal ();
            var page = tab_view.append (terminal);
            page.title = "Terminal";
            page.icon = new ThemedIcon ("utilities-terminal");

            terminal.title_changed.connect ((new_title) => {
                page.title = new_title;
                if (tab_view.get_selected_page () == page) {
                    window_title.title = new_title;
                }
            });

            tab_view.set_selected_page (page);
        }

        private void update_title () {
            var page = tab_view.get_selected_page ();
            if (page != null) {
                window_title.title = page.title;
            }
        }
    }
}
