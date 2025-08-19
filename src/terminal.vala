namespace AetherCommand {
    public class Terminal : Gtk.Box {
        private Vte.Terminal vte_terminal;
        
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
            
            try {
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
            } catch (Error e) {
                critical ("Error spawning terminal: %s", e.message);
            }
            
            append (vte_terminal);
        }
    }
}