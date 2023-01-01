

#pragma once

#include <gtkmm.h>
#include "CPlot.h"


class CmainWindow : public Gtk::Window
{
  public:
    CmainWindow();
    void on_EditDone();
  protected:
    // I lied its not just a window but also a text entry
    Gtk::Box         m_MainBox;
    Gtk::Entry       m_Entry;
    CPlot            m_PlotArea;



};

