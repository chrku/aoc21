#include "common.h"
#include "day20.h"

#include <fstream>
#include <iostream>

int main() {
  std::ifstream ifs("input/day20.txt");
  auto input = readInputLines(ifs);
  auto result_1 = day20_part1(input);
  auto result_2 = day20_part2(input);
  std::cout << result_1 << std::endl;
  std::cout << result_2 << std::endl;
  return 0;
}
