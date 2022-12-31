#include "gtest/gtest.h"
#include "day20.h"
#include "common.h"

#include <fstream>

TEST(Day20Test, Test1) {
    std::ifstream ifs("input/day20_test.txt");
    auto result = day20_part1(readInputLines(ifs));
    EXPECT_EQ(result, 35);
}

TEST(Day20Test, Test2) {
    std::ifstream ifs("input/day20_test.txt");
    auto result = day20_part2(readInputLines(ifs));
    EXPECT_EQ(result, 3351);
}

