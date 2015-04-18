// Patrik Tennberg, 2015

#include <iostream>
#include <vector>
#include <iterator>
#include <stdio.h>

bool bin_search(const std::vector<int>& vec, int v) {
  int start = 0;
  int end = vec.size() - 1;

  std::cout << "Iterative" << '\n';
  while (start <= end) {
    int middle = start + ((end - start) / 2);

    if (v > vec[middle]) {
      start = middle + 1;
    } else if (v < vec[middle]) {
      end = middle - 1;
    } else {
      return true;
    }
  };
  return false;
}

bool bin_search_r_impl(const std::vector<int>& vec, int start, int end, int v) {
  if (start > end) {
    return false;
  }
  int middle = start + ((end - start) / 2);

  if (v > vec[middle]) {
    return bin_search_r_impl(vec, middle + 1, end, v);
  } else if (v < vec[middle]) {
    return bin_search_r_impl(vec, start, middle - 1, v);
  }
  return true;
}

bool bin_search_r(const std::vector<int>& vec, int v) {
  std::cout << "Recursive" << '\n';
  return bin_search_r_impl(vec, 0, vec.size() - 1, v);
}

int main(int, char* []) {
  std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int count = 0;

  for (auto v : vec) {
    count += bin_search_r(vec, v);
  }
  if (count != (int)vec.size()) {
    std::cout << "Failed\n";
    return -1;
  }
  if (bin_search_r(vec, -1)) {
    std::cout << "Failed\n";
    return -1;
  }
  if (bin_search_r(vec, 10)) {
    std::cout << "Failed\n";
    return -1;
  }
  if (bin_search_r(vec, 100)) {
    std::cout << "Failed\n";
    return -1;
  }
  std::cout << "Success\n";
  return 0;
}
