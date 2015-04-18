// Patrik Tennberg, 2015
// The smart algorithm used in "next_permutation" found in
// The Art of computer programming Volume 4A Combinatorial Algorithms

#include <iostream>
#include <vector>
#include <algorithm>

size_t factorial(size_t n) {
  if (n == 1) {
    return n;
  }
  return n * factorial(n - 1);
}

template <typename It>
void print(It begin, It end) {
  std::for_each(begin, end, [](decltype(*begin) v) { std::cout << v; });
  std::cout << '\n';
}

void permutation(std::vector<std::vector<int>>& p, std::vector<int> v, size_t i,
                 size_t n) {
  if (i == n) {
    p.push_back(std::vector<int>(std::begin(v), std::end(v)));
  } else {
    for (size_t j = i; j < n; ++j) {
      std::swap(v[i], v[j]);
      permutation(p, v, i + 1, n);
    }
  }
}

void call_permutation() {
  std::vector<int> v{1, 2, 3};
  std::vector<std::vector<int>> p;

  permutation(p, v, 0, v.size());

  for (auto v : p) {
    for (auto a : v) {
      std::cout << a;
    }
    std::cout << '\n';
  }
  std::cout << p.size() << " permutation(s)\n";
}

template <typename It>
bool next_permutation(It begin, It end) {
  if (begin == end) return false;

  It i = begin;
  ++i;
  if (i == end) return false;

  i = end;
  --i;

  while (true) {
    It j = i;
    --i;

    if (*i < *j) {
      It k = end;

      while (*i > *--k) /* pass */;

      std::iter_swap(i, k);
      std::reverse(j, end);

      return true;
    }
    if (i == begin) {
      std::reverse(begin, end);
      return false;
    }
  }
}

void call_next_permutation() {
  std::string str = "123";

  do {
    std::cout << str << '\n';
  } while (::next_permutation(std::begin(str), std::end(str)));

  std::cout << factorial(str.length()) << " permutation(s)" << '\n';
}

std::vector<std::string> get_permutations(const std::string& str) {
  std::vector<std::string> permutations;

  if (str.empty()) {
    permutations.emplace_back("");
    return permutations;
  }
  auto first = str[0];
  auto words = get_permutations(str.substr(1));

  for (auto w : words) {
    for (auto i = 0u; i <= w.length(); i++) {
      std::string start = w.substr(0, i);
      std::string end = w.substr(i);

      permutations.emplace_back(start + first + end);
    }
  }
  return permutations;
}

void call_get_permutations() {
  auto words = get_permutations("123");

  for (auto w : words) {
    std::cout << w << '\n';
  }
  std::cout << words.size() << " permutation(s)" << '\n';
}

int main(int, char* []) {
  call_permutation();
  std::cout << "--\n";
  call_next_permutation();
  std::cout << "--\n";
  call_get_permutations();

  return 0;
}
