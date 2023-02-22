#include "common.h"
#include "day23.h"

#include <fstream>
#include <iostream>

int main() {
  auto state1 = State::constructFrom(
      {Kind::AMBER, Kind::BRONZE}, {Kind::DESERT, Kind::COPPER},
      {Kind::BRONZE, Kind::AMBER}, {Kind::DESERT, Kind::COPPER});

  SearchSpace space1{.minEnergy = 100000, .curEnergy = 0};
  space1.stack.push_back(state1);
  space1.energs.push_back(0);
  space1.evolve(state1);

  auto state2 = State::constructFrom(
      {Kind::AMBER, Kind::DESERT, Kind::DESERT, Kind::BRONZE},
      {Kind::DESERT, Kind::COPPER, Kind::BRONZE, Kind::COPPER},
      {Kind::BRONZE, Kind::BRONZE, Kind::AMBER, Kind::AMBER},
      {Kind::DESERT, Kind::AMBER, Kind::COPPER, Kind::COPPER});

  SearchSpace space2{.minEnergy = 100000, .curEnergy = 0};
  space2.stack.push_back(state2);
  space2.energs.push_back(0);
  space2.evolve(state2);

  std::cout << space1.minEnergy << " " << space2.minEnergy << std::endl;
}
