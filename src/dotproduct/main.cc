#include <iostream>
#include <random>
#include <memory>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include "utils.h"
#include "dotProduct.h"

class Benchmark {
public:
  const size_t COUNT = 100000;
  void run(size_t size);

private:
  void init(std::vector<float> &v, const size_t size);
};

void Benchmark::run(size_t size) {
  std::vector<float> v1, v2;

  init(v1, size);
  init(v2, size);

  std::vector<std::unique_ptr<Base>> vectors;
  vectors.emplace_back(new CPP());
  vectors.emplace_back(new OpenMP());
#if defined (__aarch64__)
  vectors.emplace_back(new NEONIntrinsic());
  //vectors.emplace_back(new NEONAsm());
#endif

  std::cout.setf(std::ios::fixed);

  std::cout << "size = " << size << std::endl;
  for(auto &v : vectors) {
    size_t idx = 0;
    float mac = 0.0;
    ScopedTiming st(v->getName());
    while(idx++ < COUNT) {
      mac += v->dotProduct(v1, v2);
    }
    std::cout << "mac = " << std::setprecision(6) << mac << "  ";
  }
  std::cout << std::endl;

}

void Benchmark::init(std::vector<float> &v, const size_t size) {
  std::default_random_engine e;
  std::uniform_real_distribution<float> u(1.0, 10.0);

  v.reserve(size);
  for(size_t i = 0; i < size; i++) {
     v.push_back(u(e));
  }
}

int main(int argc, char *argv[])
{
  std::unique_ptr<Benchmark> bench(new Benchmark());
  for(size_t size = 256; size <= 4096; size *= 2) {
    bench->run(size);
  }

  return 0;
}
