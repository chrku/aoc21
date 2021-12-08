#include "common.h"
#include "day5.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day5.txt");
    auto input = readInputLines(ifs);
    std::cout << day5_part1(input) << std::endl;
    std::cout << day5_part2(input) << std::endl;
    return 0;
}
