#include "common.h"
#include "day15.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day15.txt");
    auto input = readInputLines(ifs);
    std::cout << day15_part1(input) << std::endl;
    std::cout << day15_part2(input) << std::endl;
    return 0;
}
