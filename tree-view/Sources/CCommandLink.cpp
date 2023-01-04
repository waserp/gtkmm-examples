


/// @see also
/// http://en.cppreference.com/w/cpp/thread/condition_variable

//#include "Interactive/CCommandLink.h"
#include "CCommandLink.h"
#include <cstring>

#define _CRT_SECURE_NO_WARNINGS

char * CCommandLink::wait()
{
  std::unique_lock<std::mutex> lk(m_m);
  if (m_msgqueue.empty()) { // only wait on empty queue
    m_cv.wait(lk, [this] {
      //the mutex is locked during this lambda
      return !m_msgqueue.empty();
    });
  }
  char * msg = m_msgqueue.front();
  m_msgqueue.pop();
  return msg;
}

void CCommandLink::put(std::string& p_msg)
{
  char* msg = new char[p_msg.size() + 2];
  //strcpy_s(msg, p_msg.size() + 1, p_msg.c_str());
  memcpy(msg,p_msg.c_str(),p_msg.size() + 1);
  {
    std::lock_guard<std::mutex> lk(m_m);
    m_msgqueue.push(msg);
  }
  m_cv.notify_one();
}


void CCommandLink::put(char * p_msg)
{
  {
    std::lock_guard<std::mutex> lk(m_m);
    m_msgqueue.push(p_msg);
  }
  m_cv.notify_one();
}

char * CCommandLink::checkQueue()
{
  std::lock_guard<std::mutex> lk(m_m);
  if (m_msgqueue.empty()) {
    return nullptr;
  }
  char * msg = m_msgqueue.front();
  m_msgqueue.pop();
  return msg;
}
