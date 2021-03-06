#include <iostream>
#include <mutex>
#include <atomic>
#include <memory>

// SingletonEager
class SingletonEager {
 public:
  static SingletonEager & getInstance() {
    return m_instance;
  }

 private:
  static SingletonEager m_instance;

  SingletonEager() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  ~SingletonEager() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  SingletonEager(const SingletonEager & s);
  SingletonEager& operator =(const SingletonEager & s);
};

SingletonEager SingletonEager::m_instance;

// SingletonLazy
#if 1
class SingletonLazy {
 public:
  static std::unique_ptr<SingletonLazy> & getInstance() {
    std::lock_guard<std::mutex> lck(m_mtx);
    if(m_instance == nullptr) {
      m_instance.reset(new SingletonLazy());
    }

    return m_instance;
  }

  ~SingletonLazy() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

 private:
  static std::mutex m_mtx;
  static std::unique_ptr<SingletonLazy> m_instance;

  SingletonLazy() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  SingletonLazy(const SingletonLazy & s);
  SingletonLazy& operator =(const SingletonLazy & s);
};

std::mutex SingletonLazy::m_mtx;
std::unique_ptr<SingletonLazy> SingletonLazy::m_instance;

#else
class SingletonLazy {
 public:
  ~SingletonLazy() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

#if 0
  static SingletonLazy& getInstance() {
    if(m_instance == nullptr) {
      std::lock_guard<std::mutex> lck(m_mtx);
      if(m_instance == nullptr) {
        m_instance = new SingletonLazy();
      }
    }

    return *m_instance;
  }
#else
  static SingletonLazy & getInstance() {
    SingletonLazy *p = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);
    if (p == nullptr) {
      std::lock_guard<std::mutex> lck(m_mtx);
      p = m_instance.load(std::memory_order_relaxed);
      if (p == nullptr) {
        p = new SingletonLazy();
        std::atomic_thread_fence(std::memory_order_release);
        m_instance.store(p, std::memory_order_relaxed);
      }
    }

    return *p;
  }
#endif

 private:
  static std::mutex m_mtx;
  static std::atomic<SingletonLazy *> m_instance;

  SingletonLazy() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  SingletonLazy(const SingletonLazy & s);
  SingletonLazy& operator =(const SingletonLazy & s);
};

std::mutex SingletonLazy::m_mtx;
std::atomic<SingletonLazy *> SingletonLazy::m_instance(nullptr);
#endif

// local static
class SingletonLocalStatic {
 public:
  static SingletonLocalStatic & getInstance() {
    static SingletonLocalStatic instance;
    return instance;
  }

 private:
  SingletonLocalStatic() {
     std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  ~SingletonLocalStatic() {
     std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  SingletonLocalStatic(const SingletonLocalStatic & s);
  SingletonLocalStatic& operator =(const SingletonLocalStatic & s);
};


int main(int argc, char *argv[]) {
  //SingletonEager se;
  //SingletonEager *pse = new SingletonEager();
  SingletonEager & tmp1 = SingletonEager::getInstance();
  //SingletonEager t2 = SingletonEager::getInstance();
  //SingletonEager t3;
  //t3 = SingletonEager::getInstance();

  //SingletonLazy sl;
  //SingletonLazy *psl = new SingletonLazy();
  std::unique_ptr<SingletonLazy> & tmp2 = SingletonLazy::getInstance();

  //SingletonLocalStatic sls;
  //SingletonLocalStatic *psls = new SingletonLocalStatic();
  SingletonLocalStatic & tmp3 = SingletonLocalStatic::getInstance();
  
  return 0;
}
