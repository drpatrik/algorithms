#include <iostream>
#include <iterator>
#include <vector>

template <class RandomIterator>
void transpose(RandomIterator first, RandomIterator last, int m) {
  const int mn1 = (last - first - 1);
  const int n = (last - first) / m;
  std::vector<bool> visited(last - first);
  RandomIterator cycle = first;
  while (++cycle != last) {
    if (visited[cycle - first]) continue;
    int a = cycle - first;
    do {
      a = a == mn1 ? mn1 : (n * a) % mn1;
      std::swap(*(first + a), *cycle);
      visited[a] = true;
    } while ((first + a) != cycle);
  }
}

int main() {
  int a[] = {0, 1, 2, 3, 4, 5, 6, 7};
  transpose(a, a + 8, 4);
  std::copy(a, a + 8, std::ostream_iterator<int>(std::cout, " "));
}
