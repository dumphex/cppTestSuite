#include <iostream>
#include <string>
#include <chrono>
#include <ratio>
#include "utils.h"


ScopedTiming::ScopedTiming(const std::string& tag) : m_tag(tag), m_start(std::chrono::steady_clock::now()) {}

ScopedTiming::~ScopedTiming() {
  m_stop = std::chrono::steady_clock::now();
  std::chrono::milliseconds time_span = std::chrono::duration_cast<std::chrono::milliseconds>(m_stop - m_start);
  std::cout << m_tag << " took " << time_span.count() << " ms" << std::endl;
}

