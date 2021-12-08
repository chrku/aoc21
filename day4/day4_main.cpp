#include "common.h"
#include "day4.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day4.txt");
    auto input = readInputLines(ifs);
    std::cout << day4_part1(input) << std::endl;
    std::cout << day4_part2(input) << std::endl;
    return 0;
}
