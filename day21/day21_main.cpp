#include "common.h"
#include "day21.h"

#include <fstream>
#include <iostream>

int main() {
  auto result_1 = day21_part1(2, 10);
  auto result_2 = day21_part2(2, 10);
  std::cout << result_1 << std::endl;
  std::cout << result_2 << std::endl;
  return 0;
}
