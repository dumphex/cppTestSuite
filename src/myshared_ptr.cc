#include <iostream>

template<typename T>
class myshared_ptr {
  public:
    myshared_ptr(T * ptr = nullptr) : m_ptr(ptr), m_refCount(new size_t(1)) {
      std::cout << __FUNCTION__ << " is called" << std::endl;
      *m_refCount = 1;
    }

    myshared_ptr(const myshared_ptr<T> & sp) {
      std::cout << __FUNCTION__ << " is called" << std::endl;
      m_refCount = sp.m_refCount;
      (*m_refCount)++;
    }

    myshared_ptr & operator=(const myshared_ptr<T> & sp) {
      std::cout << __FUNCTION__ << " is called" << std::endl;
      if (this != &sp) {
        (*m_refCount)--;
        if (*m_refCount == 0) {
          delete m_ptr;
          m_ptr = nullptr;
        }

        m_ptr = sp.m_ptr;
        m_refCount = sp.m_refCount;
        (*m_refCount)++;
      }

      return *this;
    }

    ~myshared_ptr() {
      std::cout << __FUNCTION__ << " is called" << std::endl;
      (*m_refCount)--;
      if (*m_refCount == 0) {
        delete m_ptr;
        m_ptr = nullptr;
      }
    }

    size_t count() const {
      return *m_refCount;
    }

  private:
    T *m_ptr;
    size_t *m_refCount;
};


int main(int argc, char *argv[]) {
  myshared_ptr<int> sp1;
  std::cout << sp1.count() << std::endl;

  myshared_ptr<int> sp2(new int(10));
  std::cout << sp2.count() << std::endl;

  myshared_ptr<int> sp3(sp2);
  std::cout << sp3.count() << std::endl;

  sp1 = sp2;
  std::cout << sp1.count() << std::endl;

  return 0;
}
