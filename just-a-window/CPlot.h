
#pragma once

#include <gtkmm.h>


class CPlot : public Gtk::DrawingArea
{
public:
  CPlot();
  void ForceRedraw(void);
protected:
   //Override default signal handler:
   virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
   virtual bool on_button_press_event(GdkEventButton *event);
   virtual bool on_button_release_event(GdkEventButton *event);
   virtual bool on_motion_notify_event(GdkEventMotion *event);

private:
  float m_shift {0};
};
