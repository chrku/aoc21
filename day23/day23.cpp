
#include "day23.h"
#include "common.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <utility>

void SearchSpace::evolve(State curState) {
  if (visited.contains(curState)) {
    if (visited[curState] <= curState.curEnergy) {
      return;
    }
  }
  visited[curState] = curState.curEnergy;

  if (curState.curEnergy >= minEnergy) {
    return;
  }

  if (curState.isComplete()) {
    if (curState.curEnergy < minEnergy) {
      std::cout << curState.curEnergy << std::endl;
      for (std::size_t i = 0; i < stack.size(); ++i) {
        const auto &state = stack[i];
        auto energ = energs[i];
        std::cout << energ << std::endl;
        render(state);
      }
    }
    minEnergy = std::min(curState.curEnergy, minEnergy);
    return;
  }

  for (std::size_t i = 0; i < curState.rooms.size(); ++i) {
    const auto &room = curState.rooms[i];
    if (room.isComplete() || room.isEmptyOrOfRightKind()) {
      continue;
    }

    std::size_t roomIndex = room.getFirstNonEmpty();
    if (roomIndex == room.slots.size()) {
      continue;
    }

    const auto &slot = room.slots[roomIndex];
    if (slot.amphipod->hasMoved) {
      break;
    }

    auto [left, right] = curState.getNearestHallwaySlots(slot.position.x);

    for (; left <= right; ++left) {
      const auto &hallwaySlot = curState.hallway[left];
      if (!hallwaySlot.amphipod.has_value()) {
        State newState = curState;

        newState.curEnergy +=
            (std::abs(slot.position.x - hallwaySlot.position.x) +
             std::abs(slot.position.y - hallwaySlot.position.y)) *
            slot.amphipod->getCost();

        newState.hallway[left].amphipod.emplace(*slot.amphipod);
        newState.hallway[left].amphipod->hasMoved = true;
        newState.rooms[i].slots[roomIndex].amphipod.reset();

        newState.reduceHallway();

        stack.push_back(newState);
        energs.push_back(newState.curEnergy);
        evolve(newState);
        energs.pop_back();
        stack.pop_back();
      }
    }
  }
}

std::int64_t Amphipod::getCost() const {
  return static_cast<std::uint32_t>(kind);
}

char Amphipod::render() const {
  switch (kind) {
  case Kind::AMBER:
    return 'A';
  case Kind::BRONZE:
    return 'B';
  case Kind::COPPER:
    return 'C';
  case Kind::DESERT:
    return 'D';
  }

  return 'X';
}

std::size_t Amphipod::getRoom() const {
  switch (kind) {
  case Kind::AMBER:
    return 0;
  case Kind::BRONZE:
    return 1;
  case Kind::COPPER:
    return 2;
  case Kind::DESERT:
    return 3;
  }

  return 0;
}

void SearchSpace::render(const State &state) {
  std::cout << "#############\n";
  std::cout << "#";
  state.hallway[0].render();
  state.hallway[1].render();
  std::cout << ".";
  state.hallway[2].render();
  std::cout << ".";
  state.hallway[3].render();
  std::cout << ".";
  state.hallway[4].render();
  std::cout << ".";
  state.hallway[5].render();
  state.hallway[6].render();
  std::cout << "#\n";

  for (std::size_t i = state.rooms[0].slots.size() - 1; i >= 1; --i) {
    std::cout << "###";
    state.rooms[0].slots[i].render();
    std::cout << "#";
    state.rooms[1].slots[i].render();
    std::cout << "#";
    state.rooms[2].slots[i].render();
    std::cout << "#";
    state.rooms[3].slots[i].render();
    std::cout << "###\n";
  }

  std::cout << "  #";
  state.rooms[0].slots[0].render();
  std::cout << "#";
  state.rooms[1].slots[0].render();
  std::cout << "#";
  state.rooms[2].slots[0].render();
  std::cout << "#";
  state.rooms[3].slots[0].render();
  std::cout << "#  \n";
  std::cout << "  #########  \n";
}

bool State::isComplete() const {
  return std::all_of(rooms.begin(), rooms.end(),
                     [](const Room &r) { return r.isComplete(); });
}

void State::reduceHallway() {
  while (true) {
    bool hasMoved = false;

    for (std::int64_t i = 0; i < hallway.size(); ++i) {
      const auto &slot = hallway[i];

      if (slot.amphipod.has_value()) {
        const auto &room = rooms[slot.amphipod->getRoom()];
        if (!room.isEmptyOrOfRightKind()) {
          continue;
        }

        auto roomIndex = room.getLastEmpty();
        if (roomIndex == -1) {
          continue;
        }

        const auto &roomSlot = room.slots[roomIndex];

        auto [left, right] = getNearestRoomSlots(slot.position.x);
        if (roomSlot.position.x <= left || roomSlot.position.x >= right) {
          continue;
        }

        if (!roomSlot.amphipod.has_value()) {
          curEnergy += (std::abs(slot.position.x - roomSlot.position.x) +
                        std::abs(slot.position.y - roomSlot.position.y)) *
                       slot.amphipod->getCost();

          rooms[slot.amphipod->getRoom()].slots[roomIndex].amphipod.emplace(
              *slot.amphipod);
          hallway[i].amphipod.reset();

          hasMoved = true;
        }
      }
    }

    if (!hasMoved) {
      break;
    }
  }
}

std::pair<std::size_t, std::size_t>
State::getNearestHallwaySlots(std::int64_t xPos) const {
  std::size_t nearestLeft{0};
  std::size_t nearestRight{hallway.size() - 1};
  std::int64_t leftXPos{hallway[nearestLeft].position.x};
  std::int64_t rightXPos{hallway[nearestRight].position.x};

  std::size_t index = 0;
  for (const auto &slot : hallway) {
    if (slot.amphipod.has_value() && slot.position.x < xPos) {
      if (slot.position.x >= leftXPos) {
        leftXPos = slot.position.x;
        nearestLeft = index + 1;
      }
    }
    if (slot.amphipod.has_value() && slot.position.x > xPos) {
      if (slot.position.x <= rightXPos) {
        rightXPos = slot.position.x;
        nearestRight = index - 1;
      }
    }

    ++index;
  }

  return {nearestLeft, nearestRight};
}

std::pair<std::size_t, std::size_t>
State::getNearestRoomSlots(std::int64_t xPos) const {
  std::size_t nearestLeft{0};
  std::size_t nearestRight{hallway.size() - 1};
  std::int64_t leftXPos{hallway[nearestLeft].position.x};
  std::int64_t rightXPos{hallway[nearestRight].position.x};

  std::size_t index = 0;
  for (const auto &slot : hallway) {
    if (slot.amphipod.has_value() && slot.position.x < xPos) {
      if (slot.position.x >= leftXPos) {
        leftXPos = slot.position.x;
      }
    }
    if (slot.amphipod.has_value() && slot.position.x > xPos) {
      if (slot.position.x <= rightXPos) {
        rightXPos = slot.position.x;
      }
    }

    ++index;
  }

  return {leftXPos, rightXPos};
}

State State::constructFrom(const std::vector<Kind> &k1,
                           const std::vector<Kind> &k2,
                           const std::vector<Kind> &k3,
                           const std::vector<Kind> &k4) {
  std::vector<RoomSlot> room1;
  std::vector<RoomSlot> room2;
  std::vector<RoomSlot> room3;
  std::vector<RoomSlot> room4;

  for (std::int64_t i = k1.size() - 1; i >= 0; --i) {
    auto element = k1[i];
    auto r =
        RoomSlot{.amphipod = {{.kind = element}},
                 .position = {3, static_cast<std::int64_t>(k1.size()) - i}};
    room1.push_back(r);
  }

  for (std::int64_t i = k2.size() - 1; i >= 0; --i) {
    auto element = k2[i];
    auto r =
        RoomSlot{.amphipod = {{.kind = element}},
                 .position = {5, static_cast<std::int64_t>(k2.size()) - i}};
    room2.push_back(r);
  }

  for (std::int64_t i = k3.size() - 1; i >= 0; --i) {
    auto element = k3[i];
    auto r =
        RoomSlot{.amphipod = {{.kind = element}},
                 .position = {7, static_cast<std::int64_t>(k3.size()) - i}};
    room3.push_back(r);
  }

  for (std::int64_t i = k4.size() - 1; i >= 0; --i) {
    auto element = k4[i];
    auto r =
        RoomSlot{.amphipod = {{.kind = element}},
                 .position = {9, static_cast<std::int64_t>(k4.size()) - i}};
    room4.push_back(r);
  }

  Room rr1{room1, Kind::AMBER};
  Room rr2{room2, Kind::BRONZE};
  Room rr3{room3, Kind::COPPER};
  Room rr4{room4, Kind::DESERT};

  std::vector<Room> rooms;
  rooms.push_back(rr1);
  rooms.push_back(rr2);
  rooms.push_back(rr3);
  rooms.push_back(rr4);

  std::vector<HallwaySlot> hallwaySlots;
  auto y = static_cast<std::int64_t>(1 + k1.size());
  hallwaySlots.push_back(HallwaySlot{.amphipod = {}, .position = {1, y}});
  hallwaySlots.push_back(HallwaySlot{.amphipod = {}, .position = {2, y}});
  hallwaySlots.push_back(HallwaySlot{.amphipod = {}, .position = {4, y}});
  hallwaySlots.push_back(HallwaySlot{.amphipod = {}, .position = {6, y}});
  hallwaySlots.push_back(HallwaySlot{.amphipod = {}, .position = {8, y}});
  hallwaySlots.push_back(HallwaySlot{.amphipod = {}, .position = {10, y}});
  hallwaySlots.push_back(HallwaySlot{.amphipod = {}, .position = {11, y}});

  State state{
      .rooms = rooms,
      .hallway = hallwaySlots,
  };

  return state;
}

bool Room::isComplete() const {
  return std::all_of(slots.begin(), slots.end(), [this](const auto &o) {
    if (!o.amphipod.has_value()) {
      return false;
    }

    return o.amphipod->kind == targetKind;
  });
}

bool Room::isEmpty() const {
  return std::all_of(slots.begin(), slots.end(), [](const auto &slot) {
    return !slot.amphipod.has_value();
  });
}

Kind Room::getKind() const { return targetKind; }

bool Room::isEmptyOrOfRightKind() const {
  if (isEmpty()) {
    return true;
  }

  return std::all_of(slots.begin(), slots.end(), [this](const auto &o) {
    if (!o.amphipod.has_value()) {
      return true;
    }

    return o.amphipod->kind == targetKind;
  });
}

std::int64_t Room::getLastEmpty() const {
  for (std::int64_t i = 0; i < slots.size(); ++i) {
    const auto &slot = slots[i];
    if (!slot.amphipod.has_value()) {
      return i;
    }
  }

  return -1;
}

std::size_t Room::getFirstNonEmpty() const {
  for (std::int64_t i = slots.size() - 1; i >= 0; --i) {
    const auto &slot = slots[i];
    if (slot.amphipod.has_value()) {
      return i;
    }
  }

  return slots.size();
}

void RoomSlot::render() const {
  if (!amphipod.has_value()) {
    std::cout << ".";
  } else {
    std::cout << amphipod->render();
  }
}

void HallwaySlot::render() const {
  if (!amphipod.has_value()) {
    std::cout << ".";
  } else {
    std::cout << amphipod->render();
  }
}

std::uint64_t day23_part1(State initialState) {
  SearchSpace space{};
  space.evolve(initialState);
  return space.minEnergy;
}

std::uint64_t day23_part2() { return 0; }
