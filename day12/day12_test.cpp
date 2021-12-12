#include "gtest/gtest.h"
#include "day12.h"
#include "common.h"

#include <fstream>

TEST(Day12Test, Test1) {
    std::ifstream ifs("input/day12_test.txt");
    int val = day12_part1(readInputLines(ifs));
    EXPECT_EQ(val, 226);
}

TEST(Day12Test, Test2) {
    std::ifstream ifs("input/day12_test.txt");
    int val = day12_part2(readInputLines(ifs));
    EXPECT_EQ(val, 3509);
}
