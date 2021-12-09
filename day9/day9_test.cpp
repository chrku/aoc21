#include "gtest/gtest.h"
#include "day9.h"
#include "common.h"

#include <fstream>

TEST(Day5Test, Test1) {
    std::ifstream ifs("input/day9_test.txt");
    int val = day9_part1(readInputLines(ifs));
    EXPECT_EQ(val, 15);
}

TEST(Day5Test, Test2) {
    std::ifstream ifs("input/day9_test.txt");
    int val = day9_part2(readInputLines(ifs));
    EXPECT_EQ(val, 1134);
}
