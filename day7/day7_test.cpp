#include "gtest/gtest.h"
#include "day7.h"
#include "common.h"

#include <fstream>

TEST(Day7Test, Test1) {
    std::ifstream ifs("input/day7_test.txt");
    int val = day7_part1(readInputLines(ifs));
    EXPECT_EQ(val, 37);
}

TEST(Day7Test, Test2) {
    std::ifstream ifs("input/day7_test.txt");
    int val = day7_part2(readInputLines(ifs));
    EXPECT_EQ(val, 168);
}
