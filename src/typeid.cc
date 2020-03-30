#include <iostream>

#define PRINT(x) std::cout << "typeid("#x").name() = \"" << typeid(x).name() << "\"" << std::endl;

class Base {
 public:
  Base() : m_var(0) {}

  Base(int i) : m_var(i) {
  }

  virtual ~Base() {
    m_var = 0;
  }

 private:
  int m_var;
};

class Derived : public Base {
 public:
  Derived() : m_derived(0) {}

  Derived(int i) : m_derived(i) {
  }

  ~Derived() {
    m_derived = 0;
  }

 private:
  int m_derived;
};

void test_fundamental_type() {
  int i = 1;
  PRINT(i);

  int * const p = &i;
  PRINT(p);

  volatile float f = 2.0;
  PRINT(f);
}

void test_class_type() {
  Derived d;
  PRINT(d);

  Base *pb = &d;
  PRINT(*pb);
}

int main(int argc, char *argv[])
{
  test_fundamental_type();
  test_class_type();

  return 0;
}
