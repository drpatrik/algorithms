// Patrik Tennberg, 2015

#include <vector>
#include <climits>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <initializer_list>

template <typename T>
void print(const std::vector<T>& vec) {
  for (const auto& v:vec) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}

int minimum(int total, std::vector<int>& denominators) {
  std::vector<int> mins(total + 1, INT_MAX - 1);

  mins[0] = 0;
  std::sort(std::begin(denominators), std::end(denominators));
  for (int sum = 0;sum <= total; sum++) {
    for (auto d:denominators) {
      if (d <= sum) {
        mins[sum] = std::min(1 + mins[sum - d], mins[sum]);
      }
    }
  }
  return mins[total];
}

// (n + 1)^2 - n^2 = 2n + 1
std::vector<int> find_all_squares(int n) {
  std::vector<int> squares;
  int s = 1;

  squares.push_back(1);
  for (int i = 1;i < std::sqrt(n); i++) {
    s += (2 * i) + 1;
    n -= s;
    squares.push_back(s);
    if (n <= 0) {
      break;
    }
  }

  return squares;
}

void minimum_n_coins() {
  std::vector<int> coins = {9, 4, 1};

  std::cout << minimum(12, coins) << std::endl;
}

void minimum_squares(int n) {
  auto s = find_all_squares(n);

  std::cout << minimum(n, s) << std::endl;
}
int main(int, char *[]) {
  minimum_n_coins();
  minimum_squares(14);

  return 0;
}
