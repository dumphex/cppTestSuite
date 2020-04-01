#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include "utils.h"

class Base {
 public:
  Base() {}
  virtual ~Base() {}

  virtual void iplus(int count) = 0;
  virtual void iminus(int count) = 0;

  void bench() {
     ScopedTiming st;
     int count = 1000000;
     std::thread t1(&Base::iplus, this, count);
     std::thread t2(&Base::iminus, this, count);
     t1.join();
     t2.join();
  }

};

class Derived : public Base {
 public:
  Derived() : m_var(0) {
    std::cout << __FUNCTION__ << " : m_var = " << m_var << std::endl;
  }

  ~Derived() {
    std::cout << __FUNCTION__ << " : m_var = " << m_var << std::endl << std::endl;
  }

  void iplus(int count) {
    while (count--) {
      m_var++;
    }
  }

  void iminus(int count) {
    while (count--) {
      m_var--;
    }
  }

 private:
  int m_var;
};

class DerivedMutex : public Base {
 public:
  DerivedMutex() : m_var(0) {
    std::cout << __FUNCTION__ << " : m_var = " << m_var << std::endl;
  }

  ~DerivedMutex() {
    std::cout << __FUNCTION__ << " : m_var = " << m_var << std::endl << std::endl;
  }

  void iplus(int count) {
    while (count--) {
      std::lock_guard<std::mutex> lck(m_mtx);
      m_var++;
    }
  }

  void iminus(int count) {
    while (count--) {
      std::lock_guard<std::mutex> lck(m_mtx);
      m_var--;
    }
  }

 private:
  std::mutex m_mtx;
  int m_var;
};

class DerivedAtomic : public Base {
 public:
  DerivedAtomic() : m_var(0) {
    std::cout << __FUNCTION__ << " : m_var = " << m_var << std::endl;
  }

  ~DerivedAtomic() {
    std::cout << __FUNCTION__ << " : m_var = " << m_var << std::endl << std::endl;
  }

  void iplus(int count) {
    while (count--) {
#if 0
      m_var++;
#else
      m_var.fetch_add(1, std::memory_order_relaxed);
#endif
    }
  }

  void iminus(int count) {
    while (count--) {
#if 0
      m_var--;
#else
      m_var.fetch_sub(1, std::memory_order_relaxed);
#endif
    }
  }

 private:
  std::atomic<int> m_var;
};


int main(int argc, char *argv[]) {
  std::unique_ptr<Base> d(new Derived());
  d->bench();
  d.reset();

  d.reset(new DerivedMutex());
  d->bench();
  d.reset();

  d.reset(new DerivedAtomic());
  d->bench();

  return 0;
}
