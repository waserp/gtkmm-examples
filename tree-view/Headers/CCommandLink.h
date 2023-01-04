
#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>


class CCommandLink {
public:
   char * wait();
   char * checkQueue();
   void put(char * p_msg);
   void put(std::string& p_msg);
private:
  std::condition_variable m_cv;
  std::mutex m_m;
  std::queue<char*> m_msgqueue;
};

