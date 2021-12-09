#include "common.h"
#include "day9.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day9.txt");
    auto input = readInputLines(ifs);
    std::cout << day9_part1(input) << std::endl;
    std::cout << day9_part2(input) << std::endl;
    return 0;
}
