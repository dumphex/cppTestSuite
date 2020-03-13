#include <iostream>
#include <typeinfo>

using namespace std;

class Base {
 public:
  Base(): m_base(1) {}

  virtual ~Base() {
    m_base = 0;
  }

  virtual void foo() {
    m_base++;
  }

  virtual void bar() {
    m_base--;
  }


 private:
  int m_base;
};

class Base1 : public Base {
 public:
  Base1(): m_base1(21) {}

  virtual ~Base1() {
    m_base1 = 0;
  }

  virtual void foo() {
    m_base1++;
  }

 private:
  int m_base1;
};

class Base2 : virtual public Base {
 public:
  Base2(): m_base2(22) {}

  virtual ~Base2() {
    m_base2 = 0;
  }

  virtual void foo() {
   m_base2++;
  }

 private:
  int m_base2;
};


class Base3 : virtual public Base {
 public:
  Base3(): m_base3(23) {}

  virtual ~Base3() {
    m_base3 = 0;
  }

  virtual void foo() {
   m_base3++;
  }

 private:
  int m_base3;
};

class Derived : public Base2, public Base3 {
 public:
  Derived(): m_derived(3) {}

  virtual ~Derived() {
    m_derived = 0;
  }

  virtual void foo() {
    m_derived++;
  }

 private:
  int m_derived;
};

int main(int argc, char *argv[]) {

  Base b, *pb = nullptr;
  Base1 b1;
  Base2 b2;
  Base3 b3;
  Derived d;

  // Base and foo
  b.foo();
  pb = &b;
  pb->foo();

  // single inheritance
  b1.foo();
  b1.bar();
  pb = &b1;
  pb->foo();
  pb->bar();

  // virtual single inheritance
  pb = &b2;
  pb->foo();

  pb = &b3;
  pb->foo();

  // virtual multiple inheritance
  b2.foo();
  Base2 *pb2 = &d;
  pb2->foo();

  b3.foo();
  Base3 *pb3 = &d;
  pb3->foo();

  pb = &d;
  pb->foo();

  d.foo();
  d.bar();

  return 0;
}

