#include <iostream>

class Base {
 public:
  Base() : m_var(1) {}

  ~Base() {
    std::cout << "m_var = " << m_var << std::endl;
  }

  void foo() {
    std::cout << "this = " << this << std::endl;
    //std::cout << "&this = " << &this << std::endl;
  }

  void bar1() const {
    std::cout << "m_var = " << m_var << std::endl;
  }

  void bar2() volatile {
    std::cout << "m_var = " << m_var << std::endl;
  }

  void bar3() const volatile {
    std::cout << "m_var = " << m_var << std::endl;
  }

 private:
  int m_var;
};


int main(int argc, char *argv[]) {
  Base b;
  b.foo();
  b.bar1();
  b.bar2();
  b.bar3();

  return 0;
}
