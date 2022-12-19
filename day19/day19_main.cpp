#include "common.h"
#include "day19.h"

#include <fstream>
#include <iostream>

int main() {
  std::fstream ifs("/Users/christophkummer/src/aoc21/input/day19.txt");
  auto input = readInputLines(ifs);
  auto [first, second] = day19(input);
  std::cout << first << std::endl;
  std::cout << second << std::endl;
  return 0;
}
