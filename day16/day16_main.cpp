#include "common.h"
#include "day16.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day16.txt");
    auto input = readInputLines(ifs);
    std::cout << day16_part1(input) << std::endl;
    std::cout << day16_part2(input) << std::endl;
    return 0;
}
