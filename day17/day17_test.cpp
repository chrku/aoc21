#include "gtest/gtest.h"
#include "day18.h"
#include "common.h"

#include <fstream>

TEST(Day17Test, Test1) {
    std::ifstream ifs("input/day17_test.txt");
    auto val = day17_part1(readInputLines(ifs));
    EXPECT_EQ(val, 45);
}

TEST(Day17Test, Test2) {
    std::ifstream ifs("input/day17_test.txt");
    auto val = day17_part2(readInputLines(ifs));
    EXPECT_EQ(val, 112);
}
