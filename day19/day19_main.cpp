#include "common.h"
#include "day19.h"

#include <fstream>
#include <iostream>

int main() {
  std::fstream ifs("/Users/christophkummer/src/aoc21/input/day19.txt");
  auto input = readInputLines(ifs);
  std::cout << day19(input) << std::endl;
  return 0;
}
