#ifndef DOT_PRODUCT_H_
#define DOT_PRODUCT_H_

#include <vector>
#include <string>

class Base {
  public:
    Base(const std::string &name) : name_(name) {}
    virtual ~Base() {}

    std::string& getName() {
      return name_;
    }

    virtual float dotProduct(const std::vector<float> &v1,
                             const std::vector<float> &v2) = 0;
  private:
    std::string name_;
};


#define REGISTER_CLASS(name)                                    \
class name: public Base {                                       \
  public:                                                       \
    name() : Base(__FUNCTION__) {}                              \
    virtual ~name() {}                                          \
    virtual float dotProduct(const std::vector<float> &v1,      \
                             const std::vector<float> &v2);     \
};

REGISTER_CLASS(CPP);
REGISTER_CLASS(CPPOMP);
#if defined (__aarch64__)
REGISTER_CLASS(NEONIntrinsic);
REGISTER_CLASS(NEONAsm);
#endif

#undef REGISTER_CLASS
#endif
