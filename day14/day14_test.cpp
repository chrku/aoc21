#include "gtest/gtest.h"
#include "day14.h"
#include "common.h"

#include <fstream>

TEST(Day14Test, Test1) {
    std::ifstream ifs("input/day14_test.txt");
    int val = day14_part1(readInputLines(ifs));
    EXPECT_EQ(val, 1588);
}

TEST(Day14Test, Test2) {
    std::ifstream ifs("input/day14_test.txt");
    uint64_t val = day14_part2(readInputLines(ifs));
    EXPECT_EQ(val, 2188189693529);
}
