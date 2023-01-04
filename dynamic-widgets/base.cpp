#include <gtkmm.h>
#include "CMainWindow.h"

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

  CMainWindow window;
  window.set_default_size(600, 400);
  return app->run(window);
}
