
#pragma once


#include <gtkmm.h>

class MessageText : public Gtk::ScrolledWindow
{
public:
  MessageText();
  virtual ~MessageText();

  void insert_text(const char * p_text);

protected:
  Gtk::TextView m_TextView;
};


