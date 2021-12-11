#include "gtest/gtest.h"
#include "day8.h"
#include "common.h"

#include <fstream>

TEST(Day8Test, Test1) {
    std::ifstream ifs("input/day8_test.txt");
    int val = day8_part1(readInputLines(ifs));
    EXPECT_EQ(val, 26);
}

TEST(Day8Test, Test2) {
    std::ifstream ifs("input/day8_test.txt");
    int val = day8_part2(readInputLines(ifs));
    EXPECT_EQ(val, 61229);
}
