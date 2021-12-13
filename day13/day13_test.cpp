#include "gtest/gtest.h"
#include "day13.h"
#include "common.h"

#include <fstream>

TEST(Day13Test, Test1) {
    std::ifstream ifs("input/day13_test.txt");
    int val = day13_part1(readInputLines(ifs));
    EXPECT_EQ(val, 17);
}

TEST(Day13Test, Test2) {
    std::ifstream ifs("input/day13_test.txt");
    int val = day13_part2(readInputLines(ifs));
    EXPECT_EQ(val, 3509);
}
