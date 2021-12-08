#include "common.h"
#include "day1.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day1.txt");
    auto input = readInputLines(ifs);
    std::cout << day2_part1(input) << std::endl;
    std::cout << day2_part2(input) << std::endl;
    return 0;
}
