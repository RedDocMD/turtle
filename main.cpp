#include <gtkmm.h>

#include "top.h"

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "com.deep.logo");
  LogoWindow window;
  return app->run(window);
}
