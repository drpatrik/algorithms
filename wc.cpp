#include <iostream>
#include <string>
#include <cctype>

std::pair<size_t, size_t> count_words(const std::string& line) {
  size_t words = 0;
  size_t bytes = 0;
  bool in_word = false;

  for (auto c : line) {
    bytes++;
    if (isspace(c)) {
      if (in_word) {
        in_word = false;
        words++;
      }
      continue;
    }
    in_word = true;
  }
  return std::make_pair(words + in_word, bytes);
}

int main(int, char* []) {
  size_t lines = 0;
  size_t words = 0;
  size_t bytes = 0;
  size_t adjust_lines = 0;
  std::string line;

  while (std::cin) {
    std::getline(std::cin, line);
    if (line.empty()) {
      adjust_lines++;
    } else {
      bytes += (adjust_lines + 1);  // add eol
      lines += (adjust_lines + 1);
      adjust_lines = 0;
    }
    size_t words_in_line;
    size_t bytes_in_line;

    std::tie(words_in_line, bytes_in_line) = count_words(line);

    words += words_in_line;
    bytes +=bytes_in_line;
  }
  std::cout << '\t' << lines << '\t' << words << '\t' << bytes << '\n';

  return 0;
}
