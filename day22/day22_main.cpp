#include "common.h"
#include "day22.h"

#include <fstream>
#include <iostream>

int main() {
  std::ifstream ifs("input/day22.txt");
  auto input = readInputLines(ifs);
  auto result_1 = day22_part1(input);
  auto result_2 = day22_part2(input);
  std::cout << result_1 << std::endl;
  std::cout << result_2 << std::endl;
  return 0;
}
