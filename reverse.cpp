// Patrik Tennberg, 2015

#include <iostream>
#include <string>

template <class It1, class It2>
void reverse(It1 start, It2 end) {
  if (start == end) {
    return;
  }
  end--;
  while (start != end) {
    std::swap(start++, end--);
    if (start == end) {
      break;
    }
  }
}

int main(int c, char *args[])
{
  if (c !=2 ) {
    std::cout << "reverse str\n";
    return 0;
  }
  std::string s{args[1]};

  std::cout << s << std::endl;
  reverse(std::begin(s), std::end(s));
  std::cout << s << std::endl;
  return 0;
}
