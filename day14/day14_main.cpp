#include "common.h"
#include "day14.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day14.txt");
    auto input = readInputLines(ifs);
    std::cout << day14_part1(input) << std::endl;
    std::cout << day14_part2(input) << std::endl;
    return 0;
}
