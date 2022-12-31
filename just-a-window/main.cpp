

#include <gtkmm.h>
#include <cstdio>
#include "CmainWindow.h"

// g++ *.cpp `pkg-config gtkmm-3.0 --cflags --libs` -o mwin

// an example how to start a gtkmm GUI when you don't have the argc and argv parameters, this allows you to start a GUI for example from a library.
// just be aware the app->run function returns when the window is closed, you may want to start this in its own thread.


/*
void startDetachedGUI(int argc, char *argvv[])
{
  auto app = Gtk::Application::create(argc, argvv,"just.a.detatched.window.app");
  CmainWindow window;
  app->run(window);
}


int main(int argc, char *argv[])
{

  // define dummy parameters
  char argone[10];
  char * arguvv[]={&argone[0]};
  snprintf(argone,sizeof(argone),"foo");
  startDetachedGUI(1,arguvv);

  return 0;  
}
*/

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv,"just.a.window.app");
  CmainWindow window;
  return app->run(window);
}


