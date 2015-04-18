// Patrik Tennberg, 2015

#include <iostream>
#include <vector>

void print_subset(const std::vector<std::vector<char>>& all_sub_sets) {
  for (auto ss : all_sub_sets) {
    std::cout << '{';
    for (auto s : ss) {
      std::cout << s << ' ';
    }
    std::cout << "}\n";
  }
}

std::vector<std::vector<char>> get_subsets(std::vector<char> s,
                                           size_t index = 0) {
  std::vector<std::vector<char>> all_sub_sets;

  if (s.size() == index) {
    all_sub_sets.emplace_back(std::vector<char>());

    return all_sub_sets;
  } else {
    all_sub_sets = get_subsets(s, index + 1);

    auto item = s[index];

    std::vector<std::vector<char>> sub_sets;
    for (auto ss : all_sub_sets) {
      std::vector<char> new_ss;

      new_ss.insert(std::begin(new_ss), std::begin(ss), std::end(ss));
      new_ss.insert(std::begin(new_ss), item);
      sub_sets.insert(std::end(sub_sets), new_ss);
    }
    all_sub_sets.insert(std::end(all_sub_sets), std::begin(sub_sets),
                        std::end(sub_sets));
  }
  return all_sub_sets;
}

int main(int, char* []) {
  std::vector<char> set({'x', 'y', 'z'});

  print_subset(get_subsets(set));

  return 0;
}
