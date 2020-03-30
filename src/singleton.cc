#include <iostream>
#include <mutex>

// SingletonEager
class SingletonEager {
 public:
  ~SingletonEager() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  static SingletonEager & getInstance() {
    return m_instance;
  }

 private:
  static SingletonEager m_instance;

  SingletonEager() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }
  SingletonEager(const SingletonEager & s);
  SingletonEager& operator =(const SingletonEager & s);
};

SingletonEager SingletonEager::m_instance;

// SingletonLazy
class SingletonLazy {
 public:
  ~SingletonLazy() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

#if 1
  static SingletonLazy& getInstance() {
    std::lock_guard<std::mutex> lock(m_mtx);
    if(m_instance == nullptr) {
      m_instance = new SingletonLazy();
    }

    return *m_instance;
  }
#else
  static SingletonLazy& getInstance() {
    if(m_instance == nullptr) {
      std::lock_guard<std::mutex> lock(m_mtx);
      if(m_instance == nullptr) {
        m_instance = new SingletonLazy();
      }
    }

    return *m_instance;
  }
#endif

 private:
  static std::mutex m_mtx;
  static SingletonLazy* m_instance;

  SingletonLazy() {
    std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  SingletonLazy(const SingletonLazy & s);
  SingletonLazy& operator =(const SingletonLazy & s);
};

std::mutex SingletonLazy::m_mtx;
SingletonLazy* SingletonLazy::m_instance = nullptr;

// local static
class SingletonLocalStatic {
 public:
  ~SingletonLocalStatic() {
     std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }

  static SingletonLocalStatic & getInstance() {
    static SingletonLocalStatic instance;
    return instance;
  }

 private:
  SingletonLocalStatic() {
     std::cout << __FUNCTION__ << " is caled. " << std::endl;
  }
  SingletonLocalStatic(const SingletonLocalStatic & s);
  SingletonLocalStatic& operator =(const SingletonLocalStatic & s);
};


int main(int argc, char *argv[]) {
  //SingletonEager se;
  //SingletonEager *pse = new SingletonEager();
  SingletonEager & tmp1 = SingletonEager::getInstance();

  //SingletonLazy sl;
  //SingletonLazy *psl = new SingletonLazy();
  SingletonLazy & tmp2 = SingletonLazy::getInstance();

  //SingletonLocalStatic sls;
  //SingletonLocalStatic *psls = new SingletonLocalStatic();
  SingletonLocalStatic & tmp3 = SingletonLocalStatic::getInstance();
  
  return 0;
}
