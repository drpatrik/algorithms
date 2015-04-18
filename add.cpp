// Patrik Tennberg, 2015

#include <iostream>
#include <stdio.h>
#include <string>
#include <bitset>
#include <memory.h>
#include <limits.h>
#include <string.h>

bool is_power_2(unsigned int n) { return (n & (n - 1)) == 0; }

std::string trim_zero(const std::string& str) {
  auto p = str.find_first_not_of("0");

  return (p == std::string::npos) ? "0" : str.substr(p);
}

std::string print_hex(unsigned v) {
  char kDigits[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  const size_t kNBits = sizeof(v) * 8;
  std::string output;

  for (int i = (kNBits - 4); i >= 0; i -= 4) {
    output += kDigits[(v >> i) & 0x0F];
  }
  return "0x" + trim_zero(output);
}

template <typename T>
std::string print_binary(T v) {
  const size_t kNBits = sizeof(v) * 8;
  std::string output;

  for (int i = (kNBits - 1); i >= 0; i--) {
    output += ((v >> i) & 1) ? '1' : '0';
  }
  return "0b" + trim_zero(output);
}

int add_r(int a, int b) {
  if (b == 0) {
    return a;
  }
  int sum = a ^ b;  // Sum without carry
  int carry = (a & b) << 1;

  return add_r(sum, carry);
}

int add(int a, int b) {
  while (b != 0) {
    int sum = a ^ b;  // Sum without carry
    b = (a & b) << 1;

    a = sum;
  }
  return a;
}

int main(int, char* []) {
  char a = -127;
  unsigned char b = 127;

  printf("%d bin %s\n", a, print_binary(a).c_str());
  printf(" %u bin %s\n", b, print_binary(b).c_str());

  if (is_power_2(0x02)) {
    printf("Yes\n");
  }
  if (is_power_2(0x04)) {
    printf("Yes\n");
  }
  int sum = add(14, 1);

  printf("dec = %d\n", sum);
  printf("bin = %s\n", print_binary(sum).c_str());
  printf("hex = %s\n", print_hex(sum).c_str());

  return 0;
}
