#include "CMainWindow.h"
#include <iostream>

CMainWindow::CMainWindow()
: m_button("Hello World")   // creates a new button with label "Hello World".
{
  // Sets the border width of the window.
  set_border_width(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this, &CMainWindow::on_button_clicked));

  // This packs the button into the Window (a container).
  add(m_Fixed);
  m_Fixed.put(m_button, 100,100);
  //add(m_button);

  // The final step is to display this newly created widget...
  m_button.show();m_Fixed.show();
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::on_button_clicked()
{
  static int cnt = 0;
  static std::string ent;
  if (cnt > 4) {
    cnt = 0;
    for (auto ptr : m_vec) {
      ptr->hide();
      delete ptr;
    }
    m_vec.clear();
    return;
  }
  std::cout << "Hello World " << cnt << std::endl;
  if (cnt == 0) {
    Gtk::Entry* pnewEnt = new Gtk::Entry;
    pnewEnt->set_text("asdfasf");
    m_vec.push_back(pnewEnt);
    m_Fixed.put(*pnewEnt, 100,130 +  cnt * 30);
    pnewEnt->show();
  } else if (cnt == 1) {
    Gtk::ComboBoxText* pnewCombo = new Gtk::ComboBoxText;
    pnewCombo->append("aa","bluber");
    pnewCombo->append("bb","vodi");
    pnewCombo->set_active(1);
    m_Fixed.put(*pnewCombo, 100,130 +  cnt * 30);
    pnewCombo->show();
    m_vec.push_back(pnewCombo);
  } else if (cnt == 2) {
    Gtk::Label* pnewLabel = new Gtk::Label;
    pnewLabel->set_markup("<big>huge</big>");
    m_Fixed.put(*pnewLabel, 100,130 +  cnt * 30);
    pnewLabel->show();
    m_vec.push_back(pnewLabel);
  } else if (cnt == 3) {
    Gtk::Label* pnewLabel = new Gtk::Label;
    std::string txt = dynamic_cast<Gtk::Entry*>(m_vec[0])->get_text();
    std::cout << txt << "\n";
    pnewLabel->set_markup(txt);
    m_Fixed.put(*pnewLabel, 100,130 +  cnt * 30);
    pnewLabel->show();
    m_vec.push_back(pnewLabel);
  } else if (cnt == 4) {
    Gtk::Label* pnewLabel = new Gtk::Label;
    std::string txt = dynamic_cast<Gtk::Entry*>(m_vec[0])->get_text();
    std::cout << txt << "\n";
    pnewLabel->set_markup("<span size=\"20000\">Texting</span>");
    m_Fixed.put(*pnewLabel, 100,130 +  cnt * 30);
    pnewLabel->show();
    m_vec.push_back(pnewLabel);  // 1024th pixel
  }
  cnt++;
}
