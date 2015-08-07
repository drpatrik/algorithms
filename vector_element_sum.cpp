// Patrik Tennberg, 2015

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int>> find_sum(const std::vector<int>& vec,
                                          int sum) {
  std::vector<std::pair<int, int>> result;

  for (auto i : vec) {
    std::vector<int>::const_iterator it;
    std::vector<int>::const_iterator pos = std::begin(vec);

    do {
      it = std::find_if(pos, std::end(vec), [i, sum, &result](int j) {
        if ((i != j) && (i + j) == sum) {
          if (std::find(std::begin(result), std::end(result),
                        std::make_pair(j, i)) == std::end(result)) {
            result.emplace_back(i, j);
          }
          return true;
        }
        return false;
      });
      pos = it + 1;
    } while (it != std::end(vec));
  }
  return result;
}

int main(int, char * []) {
  std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  for (auto r : find_sum(v, 12)) {
    std::cout << r.first << "," << r.second << std::endl;
  }
  return 0;
}
