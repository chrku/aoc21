#include "common.h"
#include "day21.h"
#include "gtest/gtest.h"

#include <fstream>

TEST(Day21Test, Test1) {
  auto result = day21_part1(4, 8);
  EXPECT_EQ(result, 739785);
}

TEST(Day21Test, Test2) {
  auto result = day21_part2(4, 8);
  EXPECT_EQ(result, 444356092776315ULL);
}
