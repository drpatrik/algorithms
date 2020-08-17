#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

inline int64_t time_in_ms() {
  auto current_time = std::chrono::high_resolution_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(current_time.time_since_epoch()).count();
}

std::vector<int> create_input_data(size_t n) {
  std::mt19937 engine {std::random_device{}()};
  std::uniform_int_distribution<int> distribution { 0, INT_MAX };

  std::vector<int> v(n);

  std::generate(std::begin(v), std::end(v), [&distribution, &engine]() {
                   return distribution(engine);});

  return v;

}

std::pair<int, int> solution_one(const std::vector<int>& v) {
  std::vector<int> values( { -1, -1 });

  for (const auto e : v) {
    if (e > values[0]) {
      std::swap(values[1], values[0]);
      values[0] = e;
    } else if (e > values[1]) {
      values[1] = e;
    }
  }

  return std::make_pair(values[0], values[1]);
}

std::pair<int, int> solution_two(std::vector<int>& v) {
  std::sort(std::begin(v), std::end(v));

  return std::make_pair(v[v.size() - 1], v[v.size() - 2]);
}

const size_t N = 50000000;

int main(int, char *[]) {
  std::vector<int> v = create_input_data(N);

  auto start = time_in_ms();

  auto [v1, v2] = solution_one(v);

  std::cout << "One: "<< time_in_ms() - start << " ms" << std::endl;

  std::cout << v2 << " " << v1 << std::endl;

  start = time_in_ms();

  std::tie(v1, v2) = solution_two(v);

  std::cout << "Two: " << time_in_ms() - start << " ms" << std::endl;

  std::cout << v2 << " " << v1 << std::endl;

  return 0;
}
