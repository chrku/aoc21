#include "gtest/gtest.h"
#include "day11.h"
#include "common.h"

#include <fstream>

TEST(Day11Test, Test1) {
    std::ifstream ifs("input/day11_test.txt");
    int val = day11_part1(readInputLines(ifs));
    EXPECT_EQ(val, 1656);
}

TEST(Day11Test, Test2) {
    std::ifstream ifs("input/day11_test.txt");
    int val = day11_part2(readInputLines(ifs));
    EXPECT_EQ(val, 195);
}
