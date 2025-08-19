namespace AetherCommand {
    public class Application : Adw.Application {
        public Application () {
            Object (
                application_id: "org.aether.command",
                flags: ApplicationFlags.DEFAULT_FLAGS
            );
        }

        protected override void activate () {
            var window = new MainWindow (this);
            window.present ();
        }
    }

    public static int main (string[] args) {
        var app = new Application ();
        return app.run (args);
    }
}