#include "gtest/gtest.h"
#include "day4.h"
#include "common.h"

#include <fstream>

TEST(Day4Test, Test1) {
    std::ifstream ifs("input/day4_test.txt");
    int val = day4_part1(readInputLines(ifs));
    EXPECT_EQ(val, 4512);
}

TEST(Day4Test, Test2) {
    std::ifstream ifs("input/day4_test.txt");
    int val = day4_part2(readInputLines(ifs));
    EXPECT_EQ(val, 1924);
}

