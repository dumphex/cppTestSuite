#include<iostream>

template <typename T>
T test(T a, T b) {
  
  T s = a + b;
  return s;
}	

int main(int argc, char *argv[])
{
  float a1 = 1.0;
  float b1 = 2.0;
  float s1 = test<float>(a1, b1);
  std::cout << s1 << std::endl;

  double a2 = 1.0;
  double b2 = 2.0;
  double s2 = test<double>(a2, b2);
  std::cout << s2 << std::endl;

  return 0;
}
