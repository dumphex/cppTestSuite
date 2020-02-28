#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <chrono>

class ScopedTiming {
 public:
  ScopedTiming(const std::string &tag = "ScopedTiming");
  ~ScopedTiming();

 private:
  std::string m_tag;
  std::chrono::steady_clock::time_point m_start;
  std::chrono::steady_clock::time_point m_stop;
};


#endif
