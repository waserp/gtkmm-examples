#pragma once

#include <gtkmm.h>
#include <vector>

class CMainWindow : public Gtk::Window
{

public:
  CMainWindow();
  virtual ~CMainWindow();

protected:
  //Signal handlers:
  void on_button_clicked();



  //Member widgets:
  Gtk::Button m_button;
  Gtk::Fixed  m_Fixed;
  std::vector<Gtk::Widget*> m_vec;
};
