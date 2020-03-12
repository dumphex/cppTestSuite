#include <iostream>
#include <stdlib.h>

class Base {
 public:
  Base(int i) : m_var(i) {
    std::cout << __FUNCTION__ << " is called: m_var = " << m_var << std::endl;
  }

  ~Base() {
    std::cout << __FUNCTION__ << " is called: m_var = " << m_var << std::endl;
    m_var = 0;
  }

 private:
  int m_var;
};

Base global_obj(1);

void exit_handler() {
  std::cout << __FUNCTION__ << " is called." << std::endl;
  Base b(2);
}

int main(int argc, char *argv[]) {

  atexit(exit_handler);
  return 0;
}
