
#pragma once

#include <gtkmm.h>

class LoggerText : public Gtk::ScrolledWindow
{
public:
  LoggerText();
  virtual ~LoggerText();

  void insert_text(const char * p_text);

protected:
  Gtk::TextView m_TextView;
};


