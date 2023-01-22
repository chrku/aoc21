#ifndef AOC_DAY22_H
#define AOC_DAY22_H

#include <functional>
#include <ostream>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.h"

struct Point3D {
  std::int64_t x;
  std::int64_t y;
  std::int64_t z;
};

struct Cube {
  Point3D topRight;
  Point3D bottomLeft;

  std::optional<Cube> intersects(const Cube &cube) const;
  std::vector<Cube> cleave(const Cube &cube) const;
  std::uint64_t extent() const;
};

enum class Status { ON, OFF };

struct TaggedCube {
  Cube cube;
  Status status;
};

struct Reactor {
  std::unordered_map<std::uint64_t, TaggedCube> cubes;
  std::uint64_t curId{0};

  void insert(TaggedCube cube);
  void remove(std::uint64_t id);

public:
  std::uint64_t getNumTurnedOn() const;
  void apply(TaggedCube cube);
};

struct Input {
  std::vector<TaggedCube> cubes;

  static Input parse(std::vector<std::string> lines, std::int64_t min,
                     std::int64_t max);
};

std::uint64_t day22_part1(const std::vector<std::string> &input);

std::uint64_t day22_part2(const std::vector<std::string> &input);

#endif // AOC_DAY22_H
