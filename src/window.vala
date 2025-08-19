namespace AetherCommand {
    [GtkTemplate (ui = "/org/aether/command/window.ui")]
    public class MainWindow : Adw.ApplicationWindow {
        [GtkChild]
        private unowned Gtk.Box main_box;
        
        private Terminal terminal;

        public MainWindow (Gtk.Application app) {
            Object (application: app);
            
            setup_window ();
            setup_terminal ();
        }
        
        private void setup_window () {
            title = "Aether Command";
            icon_name = "utilities-terminal";
            default_width = 800;
            default_height = 600;
        }
        
        private void setup_terminal () {
            terminal = new Terminal ();
            main_box.append (terminal);
        }
    }
}