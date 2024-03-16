#include <iostream>
#include <string>
#include <vector>
void PrintVector(std::vector<std::string> vec) {
  std::cout << std::endl;
  for (auto it : vec) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
}
