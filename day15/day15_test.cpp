#include "gtest/gtest.h"
#include "day15.h"
#include "common.h"

#include <fstream>

TEST(Day14Test, Test1) {
    std::ifstream ifs("input/day15_test.txt");
    auto val = day15_part1(readInputLines(ifs));
    EXPECT_EQ(val, 40);
}

TEST(Day14Test, Test2) {
    std::ifstream ifs("input/day15_test.txt");
    auto val = day15_part2(readInputLines(ifs));
    EXPECT_EQ(val, 315);
}
