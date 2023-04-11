#include "common.h"
#include "day25.h"

#include <fstream>
#include <iostream>

int main() {
  std::ifstream ifs("input/day25.txt");
  auto input = readInputLines(ifs);
  std::cout << day25_part1(input) << " " << day25_part2(input) << std::endl;
}
