#include <iostream>

class Base {
 public:
  Base() : m_var(1) {
  }

  ~Base() {
    std::cout << "m_var = " << m_var << std::endl;
  }

 private:
  int m_var;
};

void delPrimitiveType() {
  int *p = new int();
  *p = 1;
  delete p;

  p = new int[128];
  delete []p;
}

void delClassType() {
  Base *p = new Base();
  delete p;

  p = new Base[128];
  delete []p;
}

int main(int argc, char *argv[]) {
  delPrimitiveType();
  delClassType();

  return 0;
}
