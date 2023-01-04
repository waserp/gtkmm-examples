
#pragma once

#include <gtkmm.h>
#include "CBaseParameter.h"


class CCommandTree: public Gtk::ScrolledWindow
{
public:
  CCommandTree();
  virtual ~CCommandTree();

  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:

    ModelColumns()   { add(m_col_name); add(m_col_Par_Root);}

    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<CParameterRoot*> m_col_Par_Root;
  };

  ModelColumns m_Columns;
  void SetFixed(Gtk::Fixed* p_Fixed) { m_pFixed = p_Fixed; }
  void AddNode(std::string p_name);
  void AddDevice(std::string p_Node,std::string p_name);
  void AddCommand(std::string p_Node, std::string  p_device, std::string p_name, std::vector<std::string> p_parameterList);

protected:

  Gtk::TreeView m_TreeView; //The Tree View.
  void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* /* column */);
  void on_treeview_row_expanded(const Gtk::TreeModel::iterator& iter, const Gtk::TreeModel::Path& path);
  void on_cursor_changed();
  bool on_button_pressed(GdkEventButton* const& event);
  Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
  Gtk::Fixed*    m_pFixed;  // area contorl for parameters etc.
  Gtk::TreeModel::iterator m_lastIter {nullptr};
  bool m_latItervalid;
  std::map<std::string, Gtk::TreeModel::Row> m_NodeMap;
  std::map<std::string, Gtk::TreeModel::Row> m_DeviceMap;
  std::vector<Gtk::Widget*> m_DecorativeParameterWidgets;
  std::vector<Gtk::Widget*> m_ParameterWidgets;

private:
  CBaseParameter::eParameterTypeId GetId(std::string& p_par);
};

