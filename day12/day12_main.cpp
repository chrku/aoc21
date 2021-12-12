#include "common.h"
#include "day12.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day12.txt");
    auto input = readInputLines(ifs);
    std::cout << day12_part1(input) << std::endl;
    std::cout << day12_part2(input) << std::endl;
    return 0;
}
