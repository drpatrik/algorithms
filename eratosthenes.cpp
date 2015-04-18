// Patrik Tennberg, 2015

#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

void print_primes(const std::vector<bool>& values) {
  size_t p = 2;
  size_t n = 0;

  for (auto i = std::begin(values) + 2; i != std::end(values); i++) {
    if (!(*i)) {
      std::cout << p << '\n';
      n++;
    }
    p++;
  }
  std::cout << n << " primes found of a total of " << values.size()
            << " numbers" << std::endl;
}

void find_primes(std::vector<bool>& values) {
  size_t p = 2;

  while (p <= sqrt(values.size())) {
    for (size_t i = p * p; i < values.size(); i += p) {
      values[i] = true;
    }
    auto r = std::find(std::begin(values) + p + 1, std::end(values), false);
    p = std::distance(std::begin(values), r);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("eratosthenes n\n");
    return 0;
  }
  std::vector<bool> values(std::stoi(argv[1]), false);

  find_primes(values);
  print_primes(values);

  return 0;
}
