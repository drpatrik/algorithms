// Patrik Tennberg, 2015
// Algorithms from "Introduction to Algorithms, 3ed"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

template <class It>
void print_vec(It start, It end) {
  for_each(start, end,
           [](const decltype(*start)& v) { std::cout << v << "\n"; });
  std::cout << "---\n";
}

template <class It>
void qsort_1(It start, It end) {
  if (start == end) {
    return;
  }
  auto p = std::next(start, std::distance(start, end) / 2);

  std::nth_element(start, p, end);

  qsort_1(start, p);
  qsort_1(p + 1, end);
}

template <class It>
void qsort_2(It start, It end) {
  if (start == end) {
    return;
  }
  auto p = *std::next(start, std::distance(start, end) / 2);

  auto left = std::partition(start, end,
                             [p](const decltype(*start)& v) { return v < p; });
  auto right = std::partition(
      left, end, [p](const decltype(*start)& v) { return p >= v; });

  qsort_2(start, left);
  qsort_2(right, end);
}

int partition(std::vector<size_t>& a, int p, int r) {
  size_t x = a[r];
  int i = p - 1;

  for (int j = p; j < r; ++j) {
    if (a[j] <= x) {
      ++i;
      std::swap(a[j], a[i]);
    }
  }
  std::swap(a[i + 1], a[r]);  // Swap pivot into place

  return i + 1;
}

void qsort_3_impl(std::vector<size_t>& a, int p, int r) {
  if (r < p) return;
  auto q = partition(a, p, r);

  // a[q] is now in place recursively sort the arrays on the left and right
  // of a[q]
  qsort_3_impl(a, p, q - 1);  // sort left
  qsort_3_impl(a, q + 1, r);  // sort right
}

void qsort_3(std::vector<size_t>& a) { qsort_3_impl(a, 0, a.size() - 1); }

int main(int, char* []) {
  std::vector<size_t> vec{1, 3, 0, 8, 325, 5, 7, 9, 4, 2, 6};

  qsort_3(vec);
  std::cout << "Done\n";
  print_vec(std::begin(vec), std::end(vec));

  return 0;
}
