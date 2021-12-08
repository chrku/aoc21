#include "gtest/gtest.h"
#include "day5.h"
#include "common.h"

#include <fstream>

TEST(Day5Test, Test1) {
    std::ifstream ifs("input/day5_test.txt");
    int val = day5_part1(readInputLines(ifs));
    EXPECT_EQ(val, 5);
}

TEST(Day5Test, Test2) {
    std::ifstream ifs("input/day5_test.txt");
    int val = day5_part2(readInputLines(ifs));
    EXPECT_EQ(val, 12);
}


