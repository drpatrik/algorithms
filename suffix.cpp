// Patrik Tennberg, 2015
// Algorithms from "Introduction to Algorithms, 3ed"

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

class SuffixTreeNode {
 public:
  SuffixTreeNode() {}

  void Insert(const std::string& s, size_t index) {
    indexes_.emplace_back(index);
    if (s.empty()) {
      return;
    }
    std::shared_ptr<SuffixTreeNode> node;

    if (nodes_.find(s[0]) != std::end(nodes_)) {
      node = nodes_[s[0]];
    } else {
      node = nodes_[s[0]] = std::make_shared<SuffixTreeNode>();
    }
    node->Insert(s.substr(1), index);
  }

  std::vector<size_t> Search(const std::string& s) const {
    if (s.empty()) {
      return indexes_;
    }
    auto first = s[0];

    if (nodes_.find(first) != std::end(nodes_)) {
      return nodes_[first]->Search(s.substr(1));
    }
    return std::vector<size_t>();
  }

 private:
  std::vector<size_t> indexes_;
  mutable std::unordered_map<char, std::shared_ptr<SuffixTreeNode>> nodes_;
};

class SuffixTree {
 public:
  SuffixTree(const std::string& s) {
    for (size_t i = 0; i < s.length(); ++i) {
      root_.Insert(s.substr(i), i);
    }
  }

  std::vector<size_t> Search(const std::string& s) {
    if (s.empty()) {
      return std::vector<size_t>();
    }
    return root_.Search(s);
  }

 private:
  SuffixTreeNode root_;
};

int main(int, char* []) {
  SuffixTree tree("bibs");

  auto indexes = tree.Search("b");

  std::cout << "Result:\n";
  for (auto i : indexes) {
    std::cout << i << '\n';
  }

  return 0;
}
