#include "common.h"
#include "day23.h"
#include "gtest/gtest.h"

TEST(Day23Test, Test1) {
  auto state = State::constructFrom(
      {Kind::BRONZE, Kind::AMBER}, {Kind::COPPER, Kind::DESERT},
      {Kind::BRONZE, Kind::COPPER}, {Kind::DESERT, Kind::AMBER});

  SearchSpace space{.minEnergy = 100000, .curEnergy = 0};
  space.stack.push_back(state);
  space.energs.push_back(0);
  space.evolve(state);

  EXPECT_EQ(space.minEnergy, 12521);
}

TEST(Day23Test, Test2) {
  auto state = State::constructFrom(
      {Kind::BRONZE, Kind::DESERT, Kind::DESERT, Kind::AMBER},
      {Kind::COPPER, Kind::COPPER, Kind::BRONZE, Kind::DESERT},
      {Kind::BRONZE, Kind::BRONZE, Kind::AMBER, Kind::COPPER},
      {Kind::DESERT, Kind::AMBER, Kind::COPPER, Kind::AMBER});

  SearchSpace space{.minEnergy = 100000, .curEnergy = 0};
  space.stack.push_back(state);
  space.energs.push_back(0);
  space.evolve(state);

  EXPECT_EQ(space.minEnergy, 44169);
}