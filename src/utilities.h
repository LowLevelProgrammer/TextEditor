#include "TextBuffer.h"
#include <iostream>
#include <string>
#include <vector>

inline void PrintLines(std::vector<std::string> vec) {
  std::cout << std::endl;
  for (auto line : vec) {
    std::cout << line << std::endl;
  }
}

inline void InsertLine(TextBuffer &tb, const std::string &line) {
  for (const auto &ch : line) {
    tb.InsertChar(ch);
  }
  tb.InsertChar('\n');
}
