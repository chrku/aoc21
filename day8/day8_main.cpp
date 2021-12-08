#include "common.h"
#include "day8.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day8.txt");
    auto input = readInputLines(ifs);
    std::cout << day8_part1(input) << std::endl;
    std::cout << day8_part2(input) << std::endl;
    return 0;
}
