
#include "day22.h"
#include "common.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <utility>

std::optional<Cube> Cube::intersects(const Cube &cube) const {
  if ((this->bottomLeft.x <= cube.topRight.x &&
       this->topRight.x >= cube.bottomLeft.x) &&
      (this->bottomLeft.y <= cube.topRight.y &&
       this->topRight.y >= cube.bottomLeft.y) &&
      (this->bottomLeft.z <= cube.topRight.z &&
       this->topRight.z >= cube.bottomLeft.z)) {
    auto smaller_max_x = std::min(this->topRight.x, cube.topRight.x);
    auto smaller_max_y = std::min(this->topRight.y, cube.topRight.y);
    auto smaller_max_z = std::min(this->topRight.z, cube.topRight.z);

    auto larger_min_x = std::max(this->bottomLeft.x, cube.bottomLeft.x);
    auto larger_min_y = std::max(this->bottomLeft.y, cube.bottomLeft.y);
    auto larger_min_z = std::max(this->bottomLeft.z, cube.bottomLeft.z);

    auto new_top_right = Point3D{smaller_max_x, smaller_max_y, smaller_max_z};
    auto new_bottom_left = Point3D{larger_min_x, larger_min_y, larger_min_z};

    return {{new_top_right, new_bottom_left}};
  } else {
    return {};
  }
}

std::vector<Cube> Cube::cleave(const Cube &cube) const {
  std::vector<Cube> result;
  Cube to_slice = *this;

  if (cube.bottomLeft.x > to_slice.bottomLeft.x) {
    Point3D new_bottom_left = to_slice.bottomLeft;
    Point3D new_top_right = {cube.bottomLeft.x - 1, to_slice.topRight.y,
                             to_slice.topRight.z};
    to_slice.bottomLeft.x = cube.bottomLeft.x;
    result.push_back({new_top_right, new_bottom_left});
  }
  if (cube.bottomLeft.y > to_slice.bottomLeft.y) {
    Point3D new_bottom_left = to_slice.bottomLeft;
    Point3D new_top_right = {to_slice.topRight.x, cube.bottomLeft.y - 1,
                             to_slice.topRight.z};
    to_slice.bottomLeft.y = cube.bottomLeft.y;
    result.push_back({new_top_right, new_bottom_left});
  }
  if (cube.bottomLeft.z > to_slice.bottomLeft.z) {
    Point3D new_bottom_left = to_slice.bottomLeft;
    Point3D new_top_right = {to_slice.topRight.x, to_slice.topRight.y,
                             cube.bottomLeft.z - 1};
    to_slice.bottomLeft.z = cube.bottomLeft.z;
    result.push_back({new_top_right, new_bottom_left});
  }

  if (cube.topRight.x < to_slice.topRight.x) {
    Point3D new_bottom_left = {cube.topRight.x + 1, to_slice.bottomLeft.y,
                               to_slice.bottomLeft.z};
    Point3D new_top_right = to_slice.topRight;
    to_slice.topRight.x = cube.topRight.x;
    result.push_back({new_top_right, new_bottom_left});
  }
  if (cube.topRight.y < to_slice.topRight.y) {
    Point3D new_bottom_left = {to_slice.bottomLeft.x, cube.topRight.y + 1,
                               to_slice.bottomLeft.z};
    Point3D new_top_right = to_slice.topRight;
    to_slice.topRight.y = cube.topRight.y;
    result.push_back({new_top_right, new_bottom_left});
  }
  if (cube.topRight.z < to_slice.topRight.z) {
    Point3D new_bottom_left = {to_slice.bottomLeft.x, to_slice.bottomLeft.y,
                               cube.topRight.z + 1};
    Point3D new_top_right = to_slice.topRight;
    to_slice.topRight.z = cube.topRight.z;
    result.push_back({new_top_right, new_bottom_left});
  }

  return result;
}

std::uint64_t Cube::extent() const {
  return (this->topRight.x - this->bottomLeft.x + 1) *
         (this->topRight.y - this->bottomLeft.y + 1) *
         (this->topRight.z - this->bottomLeft.z + 1);
}

std::uint64_t Reactor::getNumTurnedOn() const {
  std::uint64_t result = 0;
  for (const auto &pair : cubes) {
    if (pair.second.status == Status::ON) {
      result += pair.second.cube.extent();
    }
  }

  return result;
}

void Reactor::apply(TaggedCube cube) {
  Reactor new_reactor{cubes, curId};
  for (const auto &pair : cubes) {
    auto result = cube.cube.intersects(pair.second.cube);
    if (result) {
      if (pair.second.status == Status::ON) {
        auto new_cubes = pair.second.cube.cleave(*result);
        for (const auto &to_insert : new_cubes) {
          new_reactor.insert(TaggedCube{to_insert, Status::ON});
        }
        new_reactor.remove(pair.first);
      }
    }
  }

  cubes = new_reactor.cubes;
  curId = new_reactor.curId;

  if (cube.status == Status::ON) {
    insert(cube);
  }
}

void Reactor::insert(TaggedCube cube) { cubes[curId++] = cube; }
void Reactor::remove(std::uint64_t id) { cubes.erase(id); }

Input Input::parse(std::vector<std::string> lines, std::int64_t min,
                   std::int64_t max) {
  std::vector<TaggedCube> result;

  for (const auto &line : lines) {
    auto parts_1 = splitString(line, " ");
    auto parts_2 = splitString(parts_1[1], ",");
    std::vector<std::pair<std::int64_t, std::int64_t>> ranges{};
    std::transform(parts_2.begin(), parts_2.end(), std::back_inserter(ranges),
                   [&](const std::string &s) {
                     auto trimmed = s.substr(s.find_first_of("=") + 1);
                     auto coords = splitString(trimmed, "..");
                     return std::make_pair<std::uint64_t, std::uint64_t>(
                         std::stoll(coords[0]), std::stoll(coords[1]));
                   });
    Status status{Status::OFF};
    if (parts_1[0] == "on") {
      status = Status::ON;
    }

    if (ranges[0].second <= max && ranges[1].second <= max &&
        ranges[2].second <= max && ranges[0].first >= min &&
        ranges[1].first >= min && ranges[2].first >= min) {
      result.push_back(
          {Cube{Point3D{ranges[0].second, ranges[1].second, ranges[2].second},
                Point3D{ranges[0].first, ranges[1].first, ranges[2].first}},
           status});
    }
  }

  return {result};
}

std::uint64_t day22_part1(const std::vector<std::string> &lines) {
  Input input = Input::parse(lines, -50, 50);

  Reactor reactor{};
  for (const auto &cube : input.cubes) {
    reactor.apply(cube);
  }

  return reactor.getNumTurnedOn();
}

std::uint64_t day22_part2(const std::vector<std::string> &lines) {
  Input input = Input::parse(lines, std::numeric_limits<std::int64_t>::min(),
                             std::numeric_limits<std::int64_t>::max());

  Reactor reactor{};
  for (const auto &cube : input.cubes) {
    reactor.apply(cube);
  }

  return reactor.getNumTurnedOn();
}
