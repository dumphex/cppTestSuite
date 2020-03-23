#include<iostream>
#include<vector>

void test_vector() {
  std::vector<int> v;

  for(size_t i = 0; i < 100; i++) {
     std::cout << "v.size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
     v.push_back(i);
  }
}

int main(int argc, char *argv[]) {
  test_vector();

  return 0;
}
