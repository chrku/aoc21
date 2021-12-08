#include "gtest/gtest.h"
#include "day3.h"
#include "common.h"

#include <fstream>

TEST(Day3Test, Test1) {
    std::ifstream ifs("input/day3_test.txt");
    int val = day3_part1(readInputLines(ifs));
    EXPECT_EQ(val, 198);
}

TEST(Day3Test, Test2) {
    std::ifstream ifs("input/day3_test.txt");
    int val = day3_part2(readInputLines(ifs));
    EXPECT_EQ(val, 230);
}

