#include "common.h"
#include "day3.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day3.txt");
    auto input = readInputLines(ifs);
    std::cout << day3_part1(input) << std::endl;
    std::cout << day3_part2(input) << std::endl;
    return 0;
}
