#include "gtest/gtest.h"
#include "day19.h"
#include "common.h"

#include <fstream>

TEST(Day19Test, Test1) {
    std::ifstream ifs("input/day19_test.txt");
    auto [first, second] = day19(readInputLines(ifs));
    EXPECT_EQ(first, 79);
    EXPECT_EQ(second, 3621);
}
