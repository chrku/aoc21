#include "common.h"
#include "day6.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day6.txt");
    auto input = readInputLines(ifs);
    std::cout << day6_part1(input) << std::endl;
    std::cout << day6_part2(input) << std::endl;
    return 0;
}
