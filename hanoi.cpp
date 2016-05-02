// Patrik Tennberg, 2015

#include <iostream>
#include <string>
#include <stack>
#include <initializer_list>

class Tower : public std::stack<int> {
 public:
  explicit Tower(const std::string& name) : name_(name) {}
  const std::string& name() const { return name_; }

 private:
  std::string name_;
};

void print_stack(Tower tower) {
  std::cout << tower.name() << ":";

  while (!tower.empty()) {
    auto v = tower.top();
    tower.pop();
    std::cout << " " << v;
  }
  std::cout << '\n';
}

void move(int n, Tower& src, Tower& dest, Tower& buffer) {
  if (n <= 0) {
    return;
  }
  // move top n - 1 disks from src to buffer using dest as buffer
  move(n - 1, src, buffer, dest);
  // move top from src to dest
  auto d = src.top();
  src.pop();
  dest.push(d);
  // move top n - 1 disks from buffer to dest using src as buffer
  move(n - 1, buffer, dest, src);
}

int main(int, char* []) {
  Tower src("src");
  Tower buffer("buffer");
  Tower dest("dest");

  for (auto v : {1, 2}) {
    src.push(v);
  }
  move(src.size(), src, dest, buffer);

  print_stack(dest);

  return 0;
}
