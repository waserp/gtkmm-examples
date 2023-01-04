
#include "CCommandTree.h"
#include <sstream>
#include <iostream>
#include "CBaseParameter.h"


CCommandTree::CCommandTree() : m_latItervalid(false)
{
  /* Create a new scrolled window, with scrollbars only if needed */
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  add(m_TreeView);

    //Create the Tree model:
  m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  //All the items to be reordered with drag-and-drop:
  m_TreeView.set_reorderable(false);

  AddNode("DetectionCtrlNode1");
  AddNode("SMSNode2");
  AddDevice("DetectionCtrlNode1","Control");
  AddDevice("DetectionCtrlNode1","Wheels");
  AddCommand("DetectionCtrlNode1","Wheels","SetParameter",std::vector<std::string>({"int32 pos","uint8 option","float KP","float KI","float KD","float TD","float todz"}));
  AddDevice("DetectionCtrlNode1","Reference");
  AddDevice("SMSNode2","MotorEx");
  AddDevice("SMSNode2","MotorEm");
  AddCommand("SMSNode2","MotorEm","MoveAbs",std::vector<std::string>({"int32 pos","uint8 option"}));
  AddCommand("SMSNode2","MotorEm","MoveRel",std::vector<std::string>({"int32 relpos","uint8 option"}));
  AddCommand("SMSNode2","MotorEm","GetLB",std::vector<std::string>({}));


 //Fill the TreeView's model
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());

  row[m_Columns.m_col_name] = "SimpleCommands";
  row[m_Columns.m_col_Par_Root] = nullptr;
  {
    auto device = *(m_refTreeModel->append(row.children()));
    device[m_Columns.m_col_name] = "Device0";
    device[m_Columns.m_col_Par_Root] = nullptr;
    {
      auto childrow = *(m_refTreeModel->append(device.children()));
      auto CommandRoot = new CParameterRoot(501,4670018,"");
      childrow[m_Columns.m_col_name] = "Test";
      CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","1","0: Normal 1: Service"));
      CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint16,"tp Mode","2","0: Normal 1: Service"));
      CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint32,"tp Mode","3","0: Normal 1: Service"));
      CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","4","0: Normal 1: Service"));
      CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","5","0: Normal 1: Service"));
      CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","6","0: Normal 1: Service"));
      CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_float,"tp Mode","7.23","0: Normal 1: Service"));
      childrow[m_Columns.m_col_Par_Root] = CommandRoot;
    }
  }

  {
    auto childrow = *(m_refTreeModel->append(row.children()));
    auto CommandRoot = new CParameterRoot(501,4670018,"");
    childrow[m_Columns.m_col_name] = "Test";
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","1","0: Normal 1: Service"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint16,"tp Mode","2","0: Normal 1: Service"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint32,"tp Mode","3","0: Normal 1: Service"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","4","0: Normal 1: Service"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","5","0: Normal 1: Service"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint8,"tp Mode","6","0: Normal 1: Service"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_float,"tp Mode","7.23","0: Normal 1: Service"));
    childrow[m_Columns.m_col_Par_Root] = CommandRoot;
  }

/*
  CParameterRoot* CommandRoot;
  Gtk::TreeModel::Row childrow;



  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "Prepare";
    CommandRoot = new CParameterRoot(503,4670008,"");
  childrow[m_Columns.m_col_Par_Root] = CommandRoot;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "Initialize";
    CommandRoot = new CParameterRoot(503,4670002,"");
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint32,"Init Mode","1","0: Normal 1: Service"));
  childrow[m_Columns.m_col_Par_Root] = CommandRoot;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "ExecuteRun";
    CommandRoot = new CParameterRoot(503,4670008,"");
  childrow[m_Columns.m_col_Par_Root] = CommandRoot;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_name] = "R&D Commands";
  row[m_Columns.m_col_Par_Root] = nullptr;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "MoveXY";
    CommandRoot = new CParameterRoot(503,4670007,"");
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_float,"X Position [mm]","0.0"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_float,"Y Position [mm]","0.0"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_float,"Speed [m/s]","0.2"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_float,"Acell [m/s2]","0.01"));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_int8,"option","1"));
  childrow[m_Columns.m_col_Par_Root] = CommandRoot;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "Move Z Focus";
    CommandRoot = new CParameterRoot(503,4670008,"");
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_float,"Z Position [mm]",""));
  childrow[m_Columns.m_col_Par_Root] = CommandRoot;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "Move Filters";
    CommandRoot = new CParameterRoot(503,4670008,"");
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint32,"Ex Filter Number",""));
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint32,"Em Filter Number",""));
  childrow[m_Columns.m_col_Par_Root] = CommandRoot;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "Move Winker";
    CommandRoot = new CParameterRoot(503,4670008,"");
    CommandRoot->AddParameter(new CBaseParameter(CBaseParameter::PTId_uint32,"Winker Position [deg]",""));
  childrow[m_Columns.m_col_Par_Root] = CommandRoot;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_name] = "Teach Commands";
  row[m_Columns.m_col_Par_Root] = nullptr;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_name] = "jjj";
  childrow[m_Columns.m_col_Par_Root] = nullptr;
*/
  //Add the TreeView's view columns:

  m_TreeView.append_column("Name", m_Columns.m_col_name);


  //Connect signal:
  m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this, &CCommandTree::on_treeview_row_activated) );
  m_TreeView.signal_row_expanded().connect(sigc::mem_fun(*this, &CCommandTree::on_treeview_row_expanded) );
  m_TreeView.signal_cursor_changed().connect(sigc::mem_fun(*this, &CCommandTree::on_cursor_changed) );
  m_TreeView.signal_button_press_event().connect(sigc::mem_fun(*this, &CCommandTree::on_button_pressed));
  show_all_children();
}



  void CCommandTree::AddNode(std::string p_name)
  {
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_Columns.m_col_name] = p_name;
    row[m_Columns.m_col_Par_Root] = nullptr;
    std::cout << "inster " << sizeof(Gtk::TreeModel::Row) << " " << &row << "\n";
    m_NodeMap.insert(std::pair<std::string, Gtk::TreeModel::Row>(p_name,row));
  }

  void CCommandTree::AddDevice(std::string p_Node,std::string p_name)
  {
    auto it=m_NodeMap.find(p_Node);
    if (it==m_NodeMap.end()) {
      std::cout << "Node not found on device insertion\n";
      return;
    }
    Gtk::TreeModel::Row row = *(m_refTreeModel->append(it->second.children()));
    row[m_Columns.m_col_name] = p_name;
    row[m_Columns.m_col_Par_Root] = nullptr;
    m_DeviceMap.insert(std::pair<std::string, Gtk::TreeModel::Row>(p_name,row));
  }

  CBaseParameter::eParameterTypeId CCommandTree::GetId(std::string& p_par)
  {
    size_t pos = p_par.find_first_of(' ');
    if (pos == std::string::npos) {
      return CBaseParameter::PTId_undef;
    }
    p_par = p_par.substr(pos);
    return CBaseParameter::PTId_undef;  // not yet implemented the datatype is only needed for checks which are omited yet.
  }

  void CCommandTree::AddCommand(std::string p_Node, std::string  p_device, std::string p_name, std::vector<std::string> p_parameterList)
  {
    auto it=m_DeviceMap.find(p_device);
      if (it==m_NodeMap.end()) {
      std::cout << "Device not found on command insertion\n";
      return;
    }
    Gtk::TreeModel::Row row = *(m_refTreeModel->append(it->second.children()));
    row[m_Columns.m_col_name] = p_name;
    auto CommandRoot = new CParameterRoot(503,4670008,p_Node+"."+p_device);
    for (auto param : p_parameterList) {
       auto id = GetId(param);
       CommandRoot->AddParameter(new CBaseParameter(id,param,"0"));
    }
    row[m_Columns.m_col_Par_Root] = CommandRoot;
  }


CCommandTree::~CCommandTree()
{
}


void CCommandTree::on_cursor_changed()
{
  Gtk::TreeModel::Path path;
  Gtk::TreeViewColumn* focus_column;

  m_TreeView.get_cursor(path, focus_column);
  Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if (!iter) {
    return;
  }
  
  Gtk::TreeModel::Row row = *iter;
  std::cout << "Cursor changed: Name="  << row[m_Columns.m_col_name] <<  std::endl;
  CParameterRoot* pCommandRoot = row[m_Columns.m_col_Par_Root];  // get pointer to command root from selected command
  if (pCommandRoot == nullptr) return;
  std::vector<CBaseParameter*>* pVector = pCommandRoot->GetParameterVector();
  if (pVector == nullptr) return;
  if (!m_latItervalid) {  // save data from last command
    m_lastIter = iter;
    m_lastIter++;
    m_latItervalid =true;
  }
  if (m_lastIter == iter) {
    return; // nothing to do if it s still the same cmd
  }

  int32_t parnr = 0;
  Gtk::TreeModel::Row lastrow = *m_lastIter;
  CParameterRoot* pLastCommandRoot = lastrow[m_Columns.m_col_Par_Root];
  for (auto widget : m_ParameterWidgets) {  // save last commands parameters as new defaults and then delete the controls
    auto pentry = dynamic_cast<Gtk::Entry*>(widget);
    if ((pentry) && (pLastCommandRoot)) {
      pLastCommandRoot->SetParameterValue(parnr,pentry->get_text());
    }
    widget->hide();
    delete(widget);
    parnr++;
  }
  m_ParameterWidgets.clear();
  m_lastIter = iter;
  for (auto widget : m_DecorativeParameterWidgets) {  // delete labels and such
    widget->hide();
    delete(widget);
  }
  m_DecorativeParameterWidgets.clear();

  // create everything for the new command
  Gtk::Label* pNameLabel = new Gtk::Label; m_DecorativeParameterWidgets.push_back(pNameLabel);
  pNameLabel->set_markup("<span size=\"20000\">"+row[m_Columns.m_col_name] + "</span>"); m_pFixed->put(*pNameLabel, 20, 10);
  pNameLabel->show();
  int32_t parcnt = 0;
  for (auto ppar : *pVector) {
    //m_plist->AddParameter(ppar->GetName(),ppar->GetDefault());
    Gtk::Entry* pnewEnt = new Gtk::Entry;
    Gtk::Label* pnewLabel = new Gtk::Label;
    pnewLabel->set_text(ppar->GetName());
    pnewEnt->set_text(ppar->GetDefault());
    m_DecorativeParameterWidgets.push_back(pnewLabel);
    m_pFixed->put(*pnewLabel, 10, 53 +  parcnt * 30);
    pnewLabel->show();
    m_ParameterWidgets.push_back(pnewEnt);
    m_pFixed->put(*pnewEnt, 70, 50 +  parcnt * 30);
    pnewEnt->show();
    parcnt++;
  }
}

void CCommandTree::on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* /* column */)
{
  std::cout << "row activated\n";/*
  Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if(iter) {
    Gtk::TreeModel::Row row = *iter;
    std::cout << "Row activated: Name="  << row[m_Columns.m_col_name] << std::endl;
    CParameterRoot* pCommandRoot = row[m_Columns.m_col_Par_Root];  // get pointer to command root from selected command
    if (pCommandRoot == nullptr) return;
  }
  */
}

void CCommandTree::on_treeview_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path)
{
  //Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if(iter) {
    Gtk::TreeModel::Row row = *iter;
    std::cout << "Row expanded: Name="  << row[m_Columns.m_col_name] << std::endl;
  }
}


bool CCommandTree::on_button_pressed(GdkEventButton* const& event)
{
  Gtk::TreeModel::Path path;
  Gtk::TreeViewColumn* focus_column;
  m_TreeView.get_cursor(path, focus_column);
  std::cout << event->button  << " on button pressed;\n";
  Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if (!iter) {
    return false;  // no iter no do
  }
  Gtk::TreeModel::Row row = *iter;
  Glib::ustring CommandName = row[m_Columns.m_col_name];
  CParameterRoot* pCommandRoot = row[m_Columns.m_col_Par_Root];  // get pointer to command root from selected command
  if (pCommandRoot == nullptr) return true;

  std::cout << "SendCmd." << pCommandRoot->GetNodeDevice() << "." << CommandName << "(";
  bool first = true;
  for (auto parm: m_ParameterWidgets){
    if (!first) std::cout << ",";
    auto pentry = dynamic_cast<Gtk::Entry*>(parm);
    if (pentry) {
      std::cout << pentry->get_text();
    }
    first = false;
  }
  std::cout << ");\n";
  return true;
}
