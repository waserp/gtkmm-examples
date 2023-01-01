

#include "CmainWindow.h"
#include <iostream>

CmainWindow::CmainWindow(): m_MainBox(Gtk::ORIENTATION_VERTICAL)
{
  set_default_size(600, 480);
  set_title("just a window");
  
  m_Entry.set_max_length(50);
  m_Entry.set_text("hello world");
  m_Entry.signal_changed().connect(sigc::mem_fun(*this, &CmainWindow::on_EditDone));
  
  m_MainBox.pack_start(m_Entry,false, 0);
  m_MainBox.pack_start(m_PlotArea, true, true, 0); // the boolean true makes the drawing area expand to full vertical size.
  add(m_MainBox);
  show_all_children();
  //fullscreen(); // this sets the window to kiosk mode, full screen no borders. exit with alt F4
}

void CmainWindow::on_EditDone()
{
  std::cout << "text in entry is:" << m_Entry.get_text() << std::endl;
}

