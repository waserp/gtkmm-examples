
#pragma once

#include <gtkmm.h>
#include <vector>

struct SPlot {
  std::vector<float> x;
  std::vector<float> y;
};

struct SBorders {
  uint32_t LeftSpace;  // space for y axis
  uint32_t LowerSpace;  // space for x axis
  uint32_t UpperSpace;
  uint32_t RightSpace;
};

struct SZoomRectancle {
  uint32_t x1;
  uint32_t x2;
  uint32_t y1;
  uint32_t y2;
};

struct SfloatRectangle {
  float x1;
  float x2;
  float y1;
  float y2;
};

class CPlot : public Gtk::DrawingArea
{
public:
  CPlot();
  void ClearPlots();
  void AddPlot(std::vector<float>& p_x, std::vector<float>& p_y);
  void SetXlabel(std::string p_xlabel) { m_Xlabel = p_xlabel; }
  void SetYlabel(std::string p_ylabel) { m_Ylabel = p_ylabel; }
  void SetTitle(std::string p_Title) { m_Title = p_Title; }
  void ResetZoom();
  void ForceRedraw(void);
protected:
   //Override default signal handler:
   virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
   virtual bool on_button_press_event(GdkEventButton *event);
   virtual bool on_button_release_event(GdkEventButton *event);
   virtual bool on_motion_notify_event(GdkEventMotion *event);
   virtual bool on_event(GdkEvent* gdk_event);
   virtual bool on_scroll_event(GdkEventScroll* scroll_event);

private:
  void GetFormatString(float p_min, float p_max, float p_diff,char * p_str, uint32_t p_size);
  void DrawTick(const Cairo::RefPtr<Cairo::Context>& cr, bool p_labeled, bool p_vertical, float p_pos, const char * p_formstr);
  void DrawOneAxis(const Cairo::RefPtr<Cairo::Context>& cr, bool p_vertical, float p_min, float p_max);


  float m_shift {0};
  SBorders           m_Borders {100,50,20,10};
  SfloatRectangle    m_ZoomRectancle {0,0,0,0};        // mousepointer down and up coordinates
  SZoomRectancle     m_GraphArea {0,0,0,0};            // the area for the curves.
  SfloatRectangle    m_CurrentAxis {-0.3,1,0,1};          // the current axis is the according to the zoom level
  SfloatRectangle    m_ResetAxis {-0.1,1.0,-0.1,2.0};  // the reset axis is defined by the data to plot
  uint32_t           m_TickLen {5};
  bool               m_DrawZoomRectangle {false};
  std::string        m_Xlabel;
  std::string        m_Ylabel;
  std::string        m_Title;
  std::vector<SPlot> m_PlotData;
};
