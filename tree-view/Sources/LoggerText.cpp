
#include "LoggerText.h"

LoggerText::LoggerText()
{
  set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  add(m_TextView);
  insert_text("bluber");
  insert_text("TEest 2");
  insert_text("TEest 3");

  show_all_children();
}

LoggerText::~LoggerText()
{
}

void LoggerText::insert_text(const char * p_text)
{
  Glib::RefPtr<Gtk::TextBuffer> refTextBuffer = m_TextView.get_buffer();

  Gtk::TextBuffer::iterator iter = refTextBuffer->get_iter_at_offset(0);
  int line = refTextBuffer->get_line_count();
  Gtk::TextBuffer::iterator iter2 = refTextBuffer->end();
  refTextBuffer->insert(iter2,p_text);
  iter2 = refTextBuffer->end();
  refTextBuffer->insert(iter2,"\n");
}
