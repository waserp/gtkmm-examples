


#include "CPlot.h"
#include <iostream>
#include <cmath>
#include <cstring>  // snprintf is cool!!!
#include <algorithm>

#define TRANSX(xval) (((xval - m_CurrentAxis.x1) / (m_CurrentAxis.x2 - m_CurrentAxis.x1)) * (m_GraphArea.x2 - m_GraphArea.x1) + m_GraphArea.x1)
#define TRANSY(yval) (((yval - m_CurrentAxis.y2) / (m_CurrentAxis.y2 - m_CurrentAxis.y1)) * (-1) *(m_GraphArea.y2 - m_GraphArea.y1) + m_GraphArea.y1)

#define INVTRANSX(xval) (((xval - m_GraphArea.x1) / (m_GraphArea.x2 - m_GraphArea.x1)) * (m_CurrentAxis.x2 - m_CurrentAxis.x1) + m_CurrentAxis.x1)
#define INVTRANSY(yval) (((m_GraphArea.y2 - yval) / (m_GraphArea.y2 - m_GraphArea.y1)) * (m_CurrentAxis.y2 - m_CurrentAxis.y1) + m_CurrentAxis.y1)

CPlot::CPlot()
{
  add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::POINTER_MOTION_MASK | Gdk::SCROLL_MASK);
  std::vector<float> xd;
  std::vector<float> yd;
  for (float t = 0 ; t < 12.8; t+= 0.1) {  // dumy data into buffer
    xd.push_back(sin(t) * 70);
    yd.push_back(cos((t+m_shift)/2) * 20);
  }
  AddPlot(xd,yd);
  SetXlabel("Time [ms]");
  SetYlabel("Thrust [N]");
  SetTitle("Engine");
}

void CPlot::ClearPlots()
{
  m_PlotData.clear();
  ForceRedraw();
}

void CPlot::AddPlot(std::vector<float>& p_x, std::vector<float>& p_y)
{
  m_PlotData.push_back(SPlot {p_x, p_y});
  float vmin = p_x[0];
  float vmax = p_x[0];
  for (float val : p_x) {
    vmin = std::min(vmin,val);
    vmax = std::max(vmax,val);
  }
  m_ResetAxis.x1 = vmin;
  m_ResetAxis.x2 = vmax;
  vmin = p_y[0];
  vmax = p_y[0];
  for (float val : p_y) {
    vmin = std::min(vmin,val);
    vmax = std::max(vmax,val);
  }
  m_ResetAxis.y1 = vmin;
  m_ResetAxis.y2 = vmax;
  m_CurrentAxis = m_ResetAxis;
}

void CPlot::ResetZoom()
{
  m_CurrentAxis = m_ResetAxis;
}

void CPlot::GetFormatString(float p_min, float p_max, float p_diff,char * p_str, uint32_t p_size)
{
  float rpos = std::max(fabs(p_min),fabs(p_max));
  if ((rpos < 10000) && (rpos > 0.1)) {
    float logrpos = log10(rpos);
    float szdif = log10(p_diff);
    //printf("pdiff %f szdif %f %f\n",p_diff, szdif, logrpos);
    if (szdif >= -1e-50 ) {
      szdif = 0;
    } else {
      szdif = fabs(floor(szdif+1e-5));
    }
    if (szdif > 4) szdif = 4.01;
    logrpos = fabs(floor(logrpos));
    int b = static_cast<int>(logrpos);
    int a = static_cast<int>(szdif);
    snprintf(p_str,p_size,"%%%i.%if",b,a);
    return;
  }
  snprintf(p_str,p_size,"%%f");
}

void CPlot::DrawTick(const Cairo::RefPtr<Cairo::Context>& cr, bool p_labeled, bool p_vertical, float p_pos, const char * p_formstr)
{
  const uint32_t maxlen = 20;
  char tickstr[maxlen];

  int32_t efflen = snprintf(tickstr,maxlen,p_formstr,p_pos);
  //printf("efflen %i  <%s> -%s-", efflen, tickstr, p_formstr);
  float xp,yp,xp1,yp1,xd,yd;
  if (p_vertical) {
    xp = m_GraphArea.x1;
    xp1 = xp - m_TickLen;
    yp = TRANSY(p_pos);
    yp1 = yp;
    xd = -30;
    yd = 3;
  } else {
    yp = m_GraphArea.y2;
    yp1 = yp - m_TickLen;
    xp = TRANSX(p_pos);
    xp1 = xp;
    xd = efflen * -4;
    yd = 12;
  }
  cr->move_to(xp,yp);
  cr->line_to(xp1 ,yp1);

  if (p_labeled) {
    cr->move_to(xp + xd,yp + yd);
    //cr->save();
    //cr->rotate_degrees(45);
    cr->show_text(tickstr);
    //cr->restore();
    //cr->rotate_degrees(0);
  }
  cr->stroke();
}

void CPlot::DrawOneAxis(const Cairo::RefPtr<Cairo::Context>& cr, bool p_vertical, float p_min, float p_max)
{
  const uint32_t maxlen = 12;
  char formatstr[maxlen];

  double xdif = (p_max - p_min) / 10;
  double expx = floor(log10(xdif));
  xdif = xdif / exp10(expx);
  if (xdif < 1.5) xdif = 1.0;
  else if (xdif < 3) xdif = 2.0;
  else xdif = 5;
  xdif = xdif * exp10(expx);
 // printf("xdif = %f\n",xdif);
  GetFormatString(p_min, p_max, xdif,formatstr, sizeof(formatstr));

  double xtickpos = p_min - fmod(p_min, xdif);
  while (xtickpos < p_max) {
    DrawTick(cr,true,p_vertical,xtickpos,formatstr);
    xtickpos+= xdif;
  }
}

bool CPlot::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  int winwitdh = allocation.get_width();
  int winheigth = allocation.get_height();
  m_GraphArea.x1 = m_Borders.LeftSpace;
  m_GraphArea.x2 = winwitdh - m_Borders.RightSpace;
  m_GraphArea.y1 = m_Borders.UpperSpace;
  m_GraphArea.y2 = winheigth - m_Borders.LowerSpace;
  // draw plot limits, the rectancle around the actual graph
  cr->set_source_rgb(0, 0, 0);
  cr->set_line_width(2.0);
  cr->rectangle(m_Borders.LeftSpace,m_Borders.UpperSpace, m_GraphArea.x2 - m_GraphArea.x1, m_GraphArea.y2 - m_GraphArea.y1);  // not filled
  cr->stroke();
  // draw axis
  DrawOneAxis(cr, false,m_CurrentAxis.x1,m_CurrentAxis.x2);
  DrawOneAxis(cr, true,m_CurrentAxis.y1,m_CurrentAxis.y2);
  // draw data
  for (auto & OneLine : m_PlotData ) {
    cr->set_line_width(0.5);
    cr->set_source_rgb(0.8, 0.1, 0);
    uint32_t i=0;
    bool first=true;
    for (float xval : OneLine.x) {
      if (first) {
        cr->move_to(TRANSX(xval),TRANSY(OneLine.y[i]));
      }
      cr->line_to(TRANSX(xval),TRANSY(OneLine.y[i]));
      first = false;
      i++;
    }
  }
  cr->stroke();
  // draw labels
  
  cr->set_source_rgb(0, 0.1, 0.0);
  cr->set_font_size(20.0);
  cr->select_font_face("monospace",Cairo::FontSlant::FONT_SLANT_NORMAL,Cairo::FontWeight::FONT_WEIGHT_NORMAL);
  cr->move_to((m_GraphArea.x1 + m_GraphArea.x2)/2 - m_Title.size() * 10,m_GraphArea.y1 - 5);
  cr->show_text(m_Title.c_str());
  cr->stroke();
  cr->set_font_size(15.0);
  cr->move_to((m_GraphArea.x1 + m_GraphArea.x2)/2 - m_Xlabel.size() * 8,m_GraphArea.y2 + 30);
  cr->show_text(m_Xlabel.c_str());
  cr->move_to(m_GraphArea.x1 - 40 ,(m_GraphArea.y2 + m_GraphArea.y1)/2 + m_Ylabel.size() * 8);
  cr->save();
  cr->rotate_degrees(-90);
  cr->show_text(m_Ylabel.c_str());
  cr->restore();
  cr->stroke();
  //std::cout << "on draw " << winwitdh << " "<< winheigth<< "\n";
  /*
  cr->set_source_rgb(0.5, 0.1, 0.3);
  cr->rectangle(1,1, winwitdh -1, winheigth-1);  // not filled
  cr->stroke();
  */
  if (m_DrawZoomRectangle) {
    cr->set_source_rgb(0, 0, 1);
    cr->set_line_width(0.5);
    cr->rectangle(m_ZoomRectancle.x1,m_ZoomRectancle.y1 ,m_ZoomRectancle.x2 - m_ZoomRectancle.x1, m_ZoomRectancle.y2 - m_ZoomRectancle.y1);
    cr->stroke();
  }
  m_shift += 0.1;
  return true;
}

void CPlot::ForceRedraw(void)
{
  /// force redraw
  Glib::RefPtr<Gdk::Window> win = get_window();
  if (win) {
      Gdk::Rectangle r(0, 0, get_allocation().get_width(),get_allocation().get_height());
      win->invalidate_rect(r, false);
  }
}

bool CPlot::on_event(GdkEvent* gdk_event)
{
  if (gdk_event->button.type == GdkEventType::GDK_2BUTTON_PRESS) {
    ResetZoom();
    ForceRedraw();
    std::cout << "double\n";
    return true;
  }
  return false;
}

bool CPlot::on_scroll_event(GdkEventScroll* scroll_event)
{
  if (scroll_event->direction) {
    float xpos = INVTRANSX(scroll_event->x);
    float ypos = INVTRANSY(scroll_event->y);
    m_CurrentAxis.x1 = xpos - (xpos - m_CurrentAxis.x1) * 0.8;
    m_CurrentAxis.x2 = (m_CurrentAxis.x2 - xpos) * 0.8 + xpos;
    m_CurrentAxis.y1 = ypos - (ypos - m_CurrentAxis.y1) * 0.8;
    m_CurrentAxis.y2 = (m_CurrentAxis.y2 - ypos) * 0.8 + ypos;
    ForceRedraw();
  } else {
    float xpos = INVTRANSX(scroll_event->x);
    float ypos = INVTRANSY(scroll_event->y);
    m_CurrentAxis.x1 = xpos - (xpos - m_CurrentAxis.x1) * 1.25;
    m_CurrentAxis.x2 = (m_CurrentAxis.x2 - xpos) * 1.25 + xpos;
    m_CurrentAxis.y1 = ypos - (ypos - m_CurrentAxis.y1) * 1.25;
    m_CurrentAxis.y2 = (m_CurrentAxis.y2 - ypos) * 1.25 + ypos;
    ForceRedraw();
  }
  return true;
}

bool CPlot::on_button_press_event(GdkEventButton *event)
{
  m_ZoomRectancle.x1 = event->x;
  m_ZoomRectancle.y1 = event->y;
  m_DrawZoomRectangle = true;
  return true;
}

bool CPlot::on_button_release_event(GdkEventButton *event)
{
  m_ZoomRectancle.x2 = event->x;
  m_ZoomRectancle.y2 = event->y;
   m_DrawZoomRectangle = false;
   if (fabs(m_ZoomRectancle.x1 - m_ZoomRectancle.x2) < 5) {
     return true;
   }
   m_CurrentAxis.x1 = INVTRANSX(std::min(m_ZoomRectancle.x2,m_ZoomRectancle.x1));
   m_CurrentAxis.x2 = INVTRANSX(std::max(m_ZoomRectancle.x2,m_ZoomRectancle.x1));
   m_CurrentAxis.y1 = INVTRANSY(std::max(m_ZoomRectancle.y2,m_ZoomRectancle.y1));
   m_CurrentAxis.y2 = INVTRANSY(std::min(m_ZoomRectancle.y2,m_ZoomRectancle.y1));
   ForceRedraw();
   return true;
}

bool CPlot::on_motion_notify_event(GdkEventMotion *event)
{
  m_ZoomRectancle.x2 = event->x; m_ZoomRectancle.y2 = event->y;
  queue_draw();
  return true;
}


