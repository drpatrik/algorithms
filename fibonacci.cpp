// Patrik Tennberg, 2015

#include <iostream>
#include <vector>

size_t fib1(size_t n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  return fib1(n - 1) + fib1(n - 2);
}

std::vector<size_t> cache(1000000, 0);

size_t fib2(size_t n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  if (cache[n] != 0) {
    return cache[n];
  }
  cache[n] = fib2(n - 1) + fib2(n - 2);
  return cache[n];
}

size_t fib3(size_t n) {
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  size_t fib1 = 0;
  size_t fib2 = 1;
  size_t fib;

  for (size_t i = 1; i < n; i++) {
    fib = fib1 + fib2;
    fib1 = fib2;
    fib2 = fib;
  }
  return fib;
}

int main(int, char *argv[]) {
  std::cout << fib3(std::stoi(argv[1])) << '\n';

  return 0;
}
