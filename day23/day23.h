#ifndef AOC_DAY23_H
#define AOC_DAY23_H

#include <functional>
#include <limits>
#include <ostream>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.h"

enum class Kind : std::uint32_t {
  AMBER = 1,
  BRONZE = 10,
  COPPER = 100,
  DESERT = 1000
};

struct Amphipod {
  Kind kind;
  bool hasMoved{false};

  bool operator==(const Amphipod &k1) const {
    return this->kind == k1.kind && this->hasMoved == k1.hasMoved;
  }

  std::int64_t getCost() const;
  std::size_t getRoom() const;
  char render() const;
};

struct RoomSlot {
  std::optional<Amphipod> amphipod;
  Point2l position;

  void render() const;

  bool operator==(const RoomSlot &k1) const {
    return this->amphipod == k1.amphipod && this->position == k1.position;
  }
};

struct Room {
  std::vector<RoomSlot> slots;
  Kind targetKind;

  bool isComplete() const;
  bool isEmpty() const;
  Kind getKind() const;

  bool isEmptyOrOfRightKind() const;
  std::int64_t getLastEmpty() const;
  std::size_t getFirstNonEmpty() const;

  bool operator==(const Room &k1) const { return this->slots == k1.slots; }
};

struct HallwaySlot {
  std::optional<Amphipod> amphipod;
  Point2l position;

  void render() const;

  bool operator==(const HallwaySlot &h1) const {
    return this->amphipod == h1.amphipod && this->position == h1.position;
  }
};

struct State {
  bool isComplete() const;
  void reduceHallway();

  std::vector<Room> rooms;
  std::vector<HallwaySlot> hallway;
  std::uint64_t curEnergy{0};

  std::pair<std::size_t, std::size_t>
  getNearestHallwaySlots(std::int64_t xPos) const;

  std::pair<std::size_t, std::size_t>
  getNearestRoomSlots(std::int64_t xPos) const;

  bool operator==(const State &s1) const {
    return this->rooms == s1.rooms && this->hallway == s1.hallway;
  }

  static State constructFrom(const std::vector<Kind> &r1,
                             const std::vector<Kind> &r2,
                             const std::vector<Kind> &r3,
                             const std::vector<Kind> &r4);
};

namespace std {
template <> struct hash<State> {
  std::size_t operator()(const State &k) const {

    std::size_t ret = 0;

    for (const auto &slot : k.hallway) {
      if (slot.amphipod) {
        ret += slot.position.x * slot.position.y;
      }
    }

    for (const auto &room : k.rooms) {
      for (const auto &slot : room.slots) {
        if (slot.amphipod) {
          ret += slot.position.x * slot.position.y;
        }
      }
    }

    return ret;
  }
};
} // namespace std

struct SearchSpace {
  void evolve(State initial);
  static void render(const State &state);

  std::uint64_t minEnergy{std::numeric_limits<std::uint64_t>::min()};
  std::uint64_t curEnergy{0};
  std::vector<State> stack{};
  std::vector<std::size_t> energs{};

  std::unordered_map<State, std::size_t> visited{};
};

std::uint64_t day23_part1(State initialState);

std::uint64_t day23_part2();

#endif // AOC_DAY23_H
