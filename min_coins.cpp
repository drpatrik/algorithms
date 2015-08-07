#include <vector>
#include <climits>
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

int minium_n_coins(int total, std::vector<int>& coin_list) {
  std::vector<int> mins(total + 1, INT_MAX - 1);

  mins[0] = 0;
  std::sort(std::begin(coin_list), std::end(coin_list));
  for (int sum = 0;sum <= total; sum++) {
    for (auto coin:coin_list) {
      if (coin <= sum) {
        mins[sum] = std::min(1 + mins[sum - coin], mins[sum]);
      }
    }
  }
  return mins[total];
}

int main(int, char *[]) {
  std::vector<int> coins = {9, 4, 1};

  std::cout << minium_n_coins(12, coins) << std::endl;

  return 0;
}
