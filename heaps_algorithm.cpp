// Patrik Tennberg, 2020
// Implemenation of Heap's permutation algorithm from 1963

#include <vector>
#include <iostream>

size_t factorial(size_t n) {
  size_t f = 1;

  for (size_t i = 1; i <= n; ++i) {
    f *= i;
  }
  return f;
}

void print(const std::vector<int>& v) {
  for (auto e:v) {
    std::cout << e;
  }
  std::cout << std::endl;
}

void heaps_permutation(std::vector<int>& v, size_t n) {
  if (n == 1) {
    print(v);
    return;
  }
  for (size_t i = 0; i < n; ++i) {
    heaps_permutation(v, n - 1);

    if (i < n - 1) {
      if (i % 2 == 1) {
        std::swap(v[i], v[n - 1]);
      } else {
        std::swap(v[0], v[n - 1]);
      }
    }
  }
}

int main(int, char*[]) {
  std::vector<int> v({ 1, 2, 3, 4, 5 });

  heaps_permutation(v, v.size());

  std::cout << factorial(v.size()) << std::endl;
}
