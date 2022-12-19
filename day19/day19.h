#ifndef AOC_DAY19_H
#define AOC_DAY19_H

#include <functional>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.h"

enum class Axis { X = 0, MINUS_X = 1, Y = 2, MINUS_Y = 3, Z = 4, MINUS_Z = 5 };

struct Beacon {
  std::int64_t x{0};
  std::int64_t y{0};
  std::int64_t z{0};

  Beacon operator+(const Beacon &rhs) const {
    return {this->x + rhs.x, this->y + rhs.y, this->z + rhs.z};
  }
  Beacon operator-(const Beacon &rhs) const {
    return {this->x - rhs.x, this->y - rhs.y, this->z - rhs.z};
  }
  Beacon operator-() { return {-this->x, -this->y, -this->z}; }
  bool operator==(const Beacon &rhs) const {
    return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
  }

  Beacon applyAxis(Axis x_transform, Axis y_transform, Axis z_transform) const {
    Beacon ret{};

    switch (x_transform) {
    case Axis::X:
      ret.x = this->x;
      break;
    case Axis::MINUS_X:
      ret.x = -this->x;
      break;
    case Axis::Y:
      ret.x = this->y;
      break;
    case Axis::MINUS_Y:
      ret.x = -this->y;
      break;
    case Axis::Z:
      ret.x = this->z;
      break;
    case Axis::MINUS_Z:
      ret.x = -this->z;
      break;
    }

    switch (y_transform) {
    case Axis::X:
      ret.y = this->x;
      break;
    case Axis::MINUS_X:
      ret.y = -this->x;
      break;
    case Axis::Y:
      ret.y = this->y;
      break;
    case Axis::MINUS_Y:
      ret.y = -this->y;
      break;
    case Axis::Z:
      ret.y = this->z;
      break;
    case Axis::MINUS_Z:
      ret.y = -this->z;
      break;
    }

    switch (z_transform) {
    case Axis::X:
      ret.z = this->x;
      break;
    case Axis::MINUS_X:
      ret.z = -this->x;
      break;
    case Axis::Y:
      ret.z = this->y;
      break;
    case Axis::MINUS_Y:
      ret.z = -this->y;
      break;
    case Axis::Z:
      ret.z = this->z;
      break;
    case Axis::MINUS_Z:
      ret.z = -this->z;
      break;
    }

    return ret;
  }
};

namespace std {
template <> struct hash<Beacon> {
  size_t operator()(const Beacon &x) const {
    return static_cast<std::size_t>(x.x ^ x.y ^ x.z);
  }
};
} // namespace std

struct Mapping {
  std::tuple<Axis, Axis, Axis> transformation;
  Beacon offset;
  std::size_t index;
};

struct Scanner {
  std::vector<Beacon> beacons;
};

struct Input {
  std::vector<Scanner> scanners;

  static Input parse(const std::vector<std::string> &input);
};

std::pair<std::int64_t, std::int64_t> day19(const std::vector<std::string> &input);

#endif // AOC_DAY19_H
