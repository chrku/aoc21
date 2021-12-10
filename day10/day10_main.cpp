#include "common.h"
#include "day10.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day10.txt");
    auto input = readInputLines(ifs);
    std::cout << day10_part1(input) << std::endl;
    std::cout << day10_part2(input) << std::endl;
    return 0;
}
