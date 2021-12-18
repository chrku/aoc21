#include "common.h"
#include "day18.h"

#include <fstream>
#include <iostream>

int main() {
    std::fstream ifs("input/day18.txt");
    auto input = readInputLines(ifs);
    std::cout << day18_part1(input) << std::endl;
    std::cout << day18_part2(input) << std::endl;
    return 0;
}
