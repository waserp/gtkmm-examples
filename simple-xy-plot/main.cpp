

#include <gtkmm.h>
#include <cstdio>
#include "CmainWindow.h"

// g++ *.cpp `pkg-config gtkmm-3.0 --cflags --libs` -o mwin


int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv,"SimplePlot");
  CmainWindow window;
  return app->run(window);
}


