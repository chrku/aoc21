#include "gtest/gtest.h"
#include "day16.h"
#include "common.h"

#include <fstream>

TEST(Day16Test, Test1) {
    std::ifstream ifs("input/day16_test_1.txt");
    auto val = day16_part1(readInputLines(ifs));
    EXPECT_EQ(val, 16);
}

TEST(Day16Test, Test2) {
    std::ifstream ifs("input/day16_test_2.txt");
    auto val = day16_part1(readInputLines(ifs));
    EXPECT_EQ(val, 12);
}

TEST(Day16Test, Test3) {
    std::ifstream ifs("input/day16_test_3.txt");
    auto val = day16_part1(readInputLines(ifs));
    EXPECT_EQ(val, 23);
}

TEST(Day16Test, Test4) {
    std::ifstream ifs("input/day16_test_4.txt");
    auto val = day16_part1(readInputLines(ifs));
    EXPECT_EQ(val, 31);
}

TEST(Day16Test, Test5) {
    std::ifstream ifs("input/day16_test_5.txt");
    auto val = day16_part2(readInputLines(ifs));
    EXPECT_EQ(val, 3);
}

TEST(Day16Test, Test6) {
    std::ifstream ifs("input/day16_test_6.txt");
    auto val = day16_part2(readInputLines(ifs));
    EXPECT_EQ(val, 54);
}

TEST(Day16Test, Test7) {
    std::ifstream ifs("input/day16_test_7.txt");
    auto val = day16_part2(readInputLines(ifs));
    EXPECT_EQ(val, 1);
}

TEST(Day16Test, Test8) {
    std::ifstream ifs("input/day16_test_8.txt");
    auto val = day16_part2(readInputLines(ifs));
    EXPECT_EQ(val, 7);
}
