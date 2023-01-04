
#pragma once

#include "CCommandTree.h"
#include "messagetext.h"
#include "LoggerText.h"
#include <gtkmm.h>

class CMainWindow : public Gtk::Window
{
public:
  CMainWindow();
  virtual ~CMainWindow();

protected:

  //Child widgets:
  Gtk::Box m_Box;
  Gtk::Paned m_VPaned;
  Gtk::Paned m_HPaned;
  Gtk::Fixed m_Fixed;
  CCommandTree m_CommandList;
  LoggerText m_LogMessage;
};

