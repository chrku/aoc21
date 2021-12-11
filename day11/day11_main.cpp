#include "common.h"
#include "day11.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day11.txt");
    auto input = readInputLines(ifs);
    std::cout << day11_part1(input) << std::endl;
    std::cout << day11_part2(input) << std::endl;
    return 0;
}
