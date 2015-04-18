// Patrik Tennberg, 2015
// Algorithms from "Introduction to Algorithms, 3ed"

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

template <typename T>
using Compare = std::function<bool(T, T)>;

template <typename T>
T left(T i) {
  return (2 * i) + 1;
}

template <typename T>
T right(T i) {
  return (2 * i) + 2;
}

template <typename T>
void heapify(std::vector<T>& a, int i, Compare<T> cmp, size_t n) {
  auto l = left<T>(i);
  auto r = right<T>(i);

  auto cmp_result = (l < T(n) && cmp(a[l], a[i])) ? l : i;

  cmp_result = (r < T(n) && cmp(a[r], a[cmp_result])) ? r : cmp_result;

  if (cmp_result != i) {
    std::swap(a[i], a[cmp_result]);
    heapify(a, cmp_result, cmp, n);
  }
}

template <typename T>
void build_max_heap(std::vector<T>& a) {
  auto cmp = [](T a, T b) -> bool { return a > b; };

  for (int i = a.size() / 2; i >= 0; --i) {
    heapify<T>(a, i, cmp, a.size());
  }
}

template <typename T>
void build_min_heap(std::vector<T>& a) {
  auto cmp = [](T a, T b) -> bool { return a < b; };

  for (int i = a.size() / 2; i >= 0; --i) {
    heapify<T>(a, i, cmp, a.size());
  }
}

template <typename T>
bool is_max_heap(const std::vector<T>& a) {
  for (auto i = 0; i < T(a.size() / 2); ++i) {
    auto l = left<T>(i);
    auto r = right<T>(i);

    if (l < T(a.size()) && a[i] < a[l]) return false;
    if (r < T(a.size()) && a[i] < a[r]) return false;
  }

  return true;
}

template <typename T>
void heap_sort(std::vector<T>& a) {
  auto cmp = [](T a, T b) -> bool { return a > b; };

  build_max_heap(a);
  size_t n = a.size();
  for (int i = a.size() - 1; i >= 1; --i) {
    std::swap(a[0], a[i]);
    n--;
    heapify<T>(a, 0, cmp, n);
  }
}

int main(int, char* []) {
  std::vector<int> a{2, 8, 1, 14, 7, 9, 3, 4, 10, 16};
  std::vector<int> a1{2, 8, 1, 14, 7, 9, 3, 4, 10, 16};

  heap_sort<int>(a1);

  for (auto v : a1) {
    std::cout << v << '\n';
  }
  std::cout << "---\n";

  if (is_max_heap(a)) {
    std::cout << "Yes" << '\n';
  } else {
    std::cout << "No" << '\n';
  }

  build_max_heap(a);

  if (is_max_heap(a)) {
    std::cout << "Yes" << '\n';
  } else {
    std::cout << "No" << '\n';
  }

  for (auto v : a) {
    std::cout << v << '\n';
  }
  std::cout << "---\n";

  build_min_heap(a);

  if (is_max_heap(a)) {
    std::cout << "Yes" << '\n';
  }

  for (auto v : a) {
    std::cout << v << '\n';
  }
  std::cout << "---\n";

  return 0;
}
