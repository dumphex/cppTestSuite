#include <iostream>

class Base {
 public:
  Base(int i) : m_var(i) {
  }

  ~Base() {
    m_var = 0;
  }

 private:
  int m_var;
};

void stack() {
  Base stack_obj(1);
}

void heap() {
  Base *heap_obj = new Base(2);

  delete heap_obj;
}

void local_static() {
  static Base local_static_obj(3);
}

Base global_obj(4);

int main(int argc, char *argv[]) {

  stack();
  heap();
  local_static();

  return 0;
}
