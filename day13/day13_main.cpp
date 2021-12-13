#include "common.h"
#include "day13.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day13.txt");
    auto input = readInputLines(ifs);
    std::cout << day13_part1(input) << std::endl;
    std::cout << day13_part2(input) << std::endl;
    return 0;
}
