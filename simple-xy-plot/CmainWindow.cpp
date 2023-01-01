

#include "CmainWindow.h"
#include "FileReader.h"
#include <iostream>

CmainWindow::CmainWindow(): m_MainBox(Gtk::ORIENTATION_VERTICAL)
{
  set_default_size(600, 480);
  set_title("just a window .");
  
  m_Entry.set_max_length(50);
  m_Entry.set_text("hello world, what could I use the entry for?");
  m_Entry.signal_changed().connect(sigc::mem_fun(*this, &CmainWindow::on_EditDone));
  
  m_MainBox.pack_start(m_MenuBar, Gtk::PACK_SHRINK);
  CreateMenu();
  m_MainBox.pack_start(m_Entry,false, 0);
  m_MainBox.pack_start(m_PlotArea, true, true, 0); // the boolean true makes the drawing area expand to full vertical size.
  add(m_MainBox);
  //show_all_children();
  show_all();
  //fullscreen(); // this sets the window to kiosk mode, full screen no borders. exit with alt F4
}

void CmainWindow::CreateMenu()
{
   Gtk::MenuItem* pmenuFile = new Gtk::MenuItem; pmenuFile->set_label("File"); m_MenuBar.append(*pmenuFile);
   Gtk::Menu*  psubMenuFile = new Gtk::Menu; pmenuFile->set_submenu(*psubMenuFile);

   Gtk::MenuItem* pmenuFileOpen = new Gtk::MenuItem; pmenuFileOpen->set_label("_Open"); pmenuFileOpen->set_use_underline(true);
   pmenuFileOpen->signal_activate().connect([&]() {
      Gtk::FileChooserDialog dialog("Please choose a folder", Gtk::FILE_CHOOSER_ACTION_OPEN); dialog.set_transient_for(*this);
      dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);      dialog.add_button("Select", Gtk::RESPONSE_OK);
      if (Gtk::RESPONSE_OK == dialog.run()) {
        std::cout << "File selected: " << dialog.get_filename() << "\n";
        ReadDataFile(dialog.get_filename(), m_PlotArea);
      }
   });
   psubMenuFile->append(*pmenuFileOpen);

   Gtk::MenuItem* pmenuFileClose = new Gtk::MenuItem; pmenuFileClose->set_label("_Close"); pmenuFileClose->set_use_underline(true);
   pmenuFileClose->signal_activate().connect([&]() { m_PlotArea.ClearPlots(); std::cout << "Clear Plots\n"; });
   psubMenuFile->append(*pmenuFileClose);

   Gtk::MenuItem* pmenuFileQuit = new Gtk::MenuItem; pmenuFileQuit->set_label("_Quit"); pmenuFileQuit->set_use_underline(true);
   pmenuFileQuit->signal_activate().connect([&]() { std::cout << "MainMenu/File/Quit" << std::endl; hide(); });
   psubMenuFile->append(*pmenuFileQuit);

   Gtk::MenuItem* pmenuEdit = new Gtk::MenuItem; pmenuEdit->set_label("Edit"); m_MenuBar.append(*pmenuEdit);
  //Gtk::MenuItem m_menuEdit; menuEdit.set_label("Edit"); m_MenuBar.append(menuEdit);


}

void CmainWindow::on_EditDone()
{
  std::cout << "text in entry is:" << m_Entry.get_text() << std::endl;
}

