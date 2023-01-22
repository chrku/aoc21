#include "common.h"
#include "day22.h"
#include "gtest/gtest.h"

#include <fstream>

TEST(Day22Test, Test1) {
  std::ifstream ifs("input/day22_test_1.txt");
  auto result = day22_part1(readInputLines(ifs));
  EXPECT_EQ(result, 39);
}

TEST(Day22Test, Test2) {
  std::ifstream ifs("input/day22_test_2.txt");
  auto result = day22_part1(readInputLines(ifs));
  EXPECT_EQ(result, 590784);
}

TEST(Day22Test, Test3) {
  std::ifstream ifs("input/day22_test_3.txt");
  auto result = day22_part2(readInputLines(ifs));
  EXPECT_EQ(result, 2758514936282235ULL);
}
