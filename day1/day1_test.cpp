#include "gtest/gtest.h"
#include "day1.h"
#include "common.h"

#include <fstream>

TEST(Day1Test, Test1) {
    std::ifstream ifs("input/day1_test.txt");
    int val = day2_part1(readInputLines(ifs));
    EXPECT_EQ(val, 7);
}

TEST(Day1Test, Test2) {
    std::ifstream ifs("input/day1_test.txt");
    int val = day2_part2(readInputLines(ifs));
    EXPECT_EQ(val, 5);
}