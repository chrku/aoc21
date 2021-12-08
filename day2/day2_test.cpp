#include "gtest/gtest.h"
#include "day2.h"
#include "common.h"

#include <fstream>

TEST(Day2Test, Test1) {
    std::ifstream ifs("input/day2_test.txt");
    int val = day2_part1(readInputLines(ifs));
    EXPECT_EQ(val, 150);
}

TEST(Day2Test, Test2) {
    std::ifstream ifs("input/day2_test.txt");
    int val = day2_part2(readInputLines(ifs));
    EXPECT_EQ(val, 900);
}
