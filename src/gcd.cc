#include <iostream>
#include <algorithm>

int gcd(int a, int b)
{
  if (a < b) {
    std::swap(a, b);
  }

  if (b == 0) {
    return a;
  }

  return gcd(b, a % b);
}

int main(int argc, char *argv[]) {

  int ret = gcd(100, 256);
  std::cout << "ret = " << ret << std::endl;

  return 0;
}
