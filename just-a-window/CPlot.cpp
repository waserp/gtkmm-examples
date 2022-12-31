


#include "CPlot.h"
#include <iostream>
#include <cmath>


CPlot::CPlot()
{
  add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK );
}

bool CPlot::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  int winwitdh = allocation.get_width();
  int winheigth = allocation.get_height();
  std::cout << "on draw " << winwitdh << " "<< winheigth<< "\n";
  cr->set_line_width(2.0);
  cr->set_source_rgb(0.5, 0.2, 0);
  bool first=true;
  for (float t = 0 ; t < 12.8; t+= 0.1) {
    float y = sin(t) * static_cast<float>(winheigth - 5) / 2 + static_cast<float>(winheigth) / 2;
    float x = cos((t+m_shift)/2) * static_cast<float>(winwitdh - 5) / 2 + static_cast<float>(winwitdh) / 2;
    if (first) {
      cr->move_to(x,y);
    }
    cr->line_to(x,y);
    first = false;
  }
  cr->stroke();
  cr->set_source_rgb(0, 0.2, 0.5);
  cr->set_font_size(18.0);
  cr->select_font_face("monospace",Cairo::FontSlant::FONT_SLANT_NORMAL,Cairo::FontWeight::FONT_WEIGHT_NORMAL);
  cr->move_to(150,150);
  cr->show_text("WWWWWWW");
  cr->move_to(150,170);
  cr->show_text("iiiiiii");
  cr->stroke();
  cr->set_source_rgb(0.5, 0.1, 0.3);
  cr->rectangle(1,1, winwitdh -1, winheigth-1);  // not filled
  cr->stroke();
  m_shift += 0.1;
  return true;
}

void CPlot::ForceRedraw(void)
{
  /// force redraw
  Glib::RefPtr<Gdk::Window> win = get_window();
  if (win) {
      Gdk::Rectangle r(0, 0, get_allocation().get_width(),get_allocation().get_height());
      std::cout << "on force " << get_allocation().get_width() << " " << get_allocation().get_height() << "\n";
      win->invalidate_rect(r, false);
  }
}

bool CPlot::on_button_press_event(GdkEventButton *event)
{
  uint32_t x1=event->x; uint32_t y1=event->y;
  std::cout << "mouse press " << x1 << " "<< y1 << "\n";
  //m_ZoomData.x1 = event->x; m_ZoomData.y1 = event->y;
  return true;
}

bool CPlot::on_button_release_event(GdkEventButton *event)
{
   int32_t x1=event->x; int32_t y1=event->y;
   std::cout << "mouse release " << x1 << " "<< y1 << "\n";
   return true;
}

bool CPlot::on_motion_notify_event(GdkEventMotion *event)
{
  uint32_t x1=event->x; uint32_t y1=event->y;
  //printf("mouse motion  %i %i \n",x1,y1);
  //m_ZoomData.x2 = event->x; m_ZoomData.y2 = event->y;
  //queue_draw();
  return true;
}


