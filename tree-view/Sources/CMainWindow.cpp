
#include "CMainWindow.h"
/*

Defines the following layout

+----------------------------------------------------------------------------+
|                                                                            |
| +-------------------+----------------------------+-----------------------+ |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |   Commnadview     |       Parameterview        |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| |                   |                            |                       | |
| +-------------------+----------------------------+-----------------------+ |
|                                                                            |
|                                                                            |
|                LogMessage                                                  |
|                                                                            |
+----------------------------------------------------------------------------+

*/

CMainWindow::CMainWindow()
:  m_Box(Gtk::ORIENTATION_VERTICAL), m_VPaned(Gtk::ORIENTATION_VERTICAL) , m_HPaned(Gtk::ORIENTATION_HORIZONTAL)
{
  set_title ("Paned Windows");
  set_border_width(2);
  set_default_size(1050, 800);

  //Add the MenuBar to the window:
  //m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);
  //m_Box.pack_end(m_VPaned);

  /* Add a vpaned widget to our toplevel window */
  add(m_VPaned);

  /* Now add the contents of the two halves of the window */
  m_VPaned.add1(m_HPaned);
  m_VPaned.add2(m_LogMessage); // log text bottom
  m_VPaned.set_position(600);
  m_VPaned.set_wide_handle(true);
  m_HPaned.add1(m_CommandList);
  m_HPaned.add2(m_Fixed);
  m_HPaned.set_position(500);
  m_HPaned.set_wide_handle(true);
  show_all_children();
  //m_CommandList.SetPlist(&m_ParameterList);
  m_CommandList.SetFixed(&m_Fixed);
}

CMainWindow::~CMainWindow()
{
}


