#include "gtest/gtest.h"
#include "day6.h"
#include "common.h"

#include <fstream>

TEST(Day5Test, Test1) {
    std::ifstream ifs("input/day6_test.txt");
    int val = day6_part1(readInputLines(ifs));
    EXPECT_EQ(val, 5934);
}

TEST(Day5Test, Test2) {
    std::ifstream ifs("input/day6_test.txt");
    auto val = day6_part2(readInputLines(ifs));
    EXPECT_EQ(val, 26984457539UL);
}


