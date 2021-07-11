#include "top.h"
#include <gtkmm.h>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create("com.deep.logo");
    return app->make_window_and_run<LogoWindow>(argc, argv);
}
