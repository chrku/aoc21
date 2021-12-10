#include "gtest/gtest.h"
#include "day10.h"
#include "common.h"

#include <fstream>

TEST(Day5Test, Test1) {
    std::ifstream ifs("input/day10_test.txt");
    int val = day10_part1(readInputLines(ifs));
    EXPECT_EQ(val, 26397);
}

TEST(Day5Test, Test2) {
    std::ifstream ifs("input/day10_test.txt");
    int val = day10_part2(readInputLines(ifs));
    EXPECT_EQ(val, 288957);
}
