#include "common.h"
#include "day7.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day7.txt");
    auto input = readInputLines(ifs);
    std::cout << day7_part1(input) << std::endl;
    std::cout << day7_part2(input) << std::endl;
    return 0;
}
