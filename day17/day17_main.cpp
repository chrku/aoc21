#include "common.h"
#include "day17.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day17.txt");
    auto input = readInputLines(ifs);
    std::cout << day17_part1(input) << std::endl;
    std::cout << day17_part2(input) << std::endl;
    return 0;
}
