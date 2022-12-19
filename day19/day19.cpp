
#include "day19.h"
#include "common.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <utility>

Input Input::parse(const std::vector<std::string> &input) {
  std::vector<std::string> cleaned;

  std::cout << "start parsing" << std::endl;

  for (const auto &line : input) {
    auto trimmed = trim_copy(line);
    if (!trimmed.empty()) {
      cleaned.push_back(std::move(trimmed));
    }
  }

  Input result;
  Scanner scanner;

  for (const auto &line : cleaned) {
    if (line.find("scanner") == std::string::npos) {
      auto parts = splitString(line, ",");
      scanner.beacons.push_back(
          {std::stoll(parts[0]), std::stoll(parts[1]), std::stoll(parts[2])});
    } else if (!scanner.beacons.empty()) {
      result.scanners.push_back(std::move(scanner));
      scanner = {};
    }
  }

  result.scanners.push_back(std::move(scanner));

  std::cout << "parsed" << std::endl;

  return result;
}

static Axis getNegative(Axis input) {
  switch (input) {
  case Axis::X:
    return Axis::MINUS_X;
  case Axis::MINUS_X:
    return Axis::X;
  case Axis::Y:
    return Axis::MINUS_Y;
  case Axis::MINUS_Y:
    return Axis::Y;
  case Axis::Z:
    return Axis::MINUS_Z;
  case Axis::MINUS_Z:
    return Axis::Z;
  }
}

static std::vector<std::tuple<Axis, Axis, Axis>> getTransformations() {
  std::vector<std::tuple<Axis, Axis, Axis>> ret_val{};

  for (std::size_t i = 0; i < 6; ++i) {
    Axis x_axis = static_cast<Axis>(i);
    for (std::size_t j = 0; j < 6; ++j) {
      Axis y_axis = static_cast<Axis>(j);
      if (y_axis != x_axis && y_axis != getNegative(x_axis)) {
        for (std::size_t k = 0; k < 6; ++k) {
          Axis z_axis = static_cast<Axis>(k);
          if (z_axis != x_axis && z_axis != getNegative(x_axis) &&
              z_axis != y_axis && z_axis != getNegative(y_axis)) {
            ret_val.push_back({x_axis, y_axis, z_axis});
          }
        }
      }
    }
  }

  return ret_val;
}

std::int64_t
find_region(const std::vector<std::tuple<Axis, Axis, Axis>> &transformations,
            std::size_t i, const std::vector<Beacon> &beacons_1,
            std::multimap<std::size_t, Mapping> &mappings, std::size_t j,
            const std::vector<Beacon> &beacons_2) {
  for (const auto &transformation : transformations) {
    for (std::size_t k = 0; k < beacons_1.size(); ++k) {
      auto [x_trf, y_trf, z_trf] = transformation;

      const auto &beacon_1 = beacons_1[k];

      for (std::size_t l = 0; l < beacons_2.size(); ++l) {
        const auto &beacon_2 = beacons_2[l].applyAxis(x_trf, y_trf, z_trf);
        auto offset = beacon_2 - beacon_1;
        std::size_t local_overlap = 0;

        for (std::size_t h = 0; h < beacons_2.size(); ++h) {
          auto translated =
              beacons_2[h].applyAxis(x_trf, y_trf, z_trf) - offset;
          if (std::find(beacons_1.begin(), beacons_1.end(), translated) !=
              beacons_1.end()) {
            local_overlap += 1;
          }
        }

        if (local_overlap >= 12) {
          mappings.insert({i,
                           {.transformation = transformation,
                            .offset = -offset,
                            .index = j}});
          return local_overlap;
        }
      }
    }
  }

  return 0;
}

void dfs(std::size_t index, const std::multimap<std::size_t, Mapping> &mappings,
         Beacon &offset, std::vector<std::tuple<Axis, Axis, Axis>> &trf_stack,
         std::set<std::size_t> visited, std::vector<Beacon> &relative_zero,
         Input const &scanners, std::vector<Beacon> &scanner_pos_zero) {

  if (!visited.contains(index)) {
    visited.insert(index);

    for (auto beacon : scanners.scanners[index].beacons) {
      for (auto it = trf_stack.rbegin(); it != trf_stack.rend(); ++it) {
        auto [x_trf, y_trf, z_trf] = *it;
        beacon = beacon.applyAxis(x_trf, y_trf, z_trf);
      }

      beacon = beacon + offset;

      relative_zero.push_back(beacon);
    }

    auto [begin, end] = mappings.equal_range(index);

    for (auto it = begin; it != end; ++it) {
      auto local_offset = it->second.offset;
      for (auto it = trf_stack.rbegin(); it != trf_stack.rend(); ++it) {
        auto [x_trf, y_trf, z_trf] = *it;
        local_offset = local_offset.applyAxis(x_trf, y_trf, z_trf);
      }
      offset = offset + local_offset;
      trf_stack.push_back(it->second.transformation);
      scanner_pos_zero.push_back(offset);
      dfs(it->second.index, mappings, offset, trf_stack, visited, relative_zero,
          scanners, scanner_pos_zero);
      offset = offset - local_offset;
      trf_stack.pop_back();
    }
  }
}

std::pair<std::int64_t, std::int64_t>
day19(const std::vector<std::string> &input) {

  Input scanners = Input::parse(input);
  auto transformations = getTransformations();

  std::multimap<std::size_t, Mapping> mappings;

  // For overlapping regions

  std::int64_t total_sum = 0;

  for (std::size_t i = 0; i < scanners.scanners.size(); ++i) {
    const auto &beacons_1 = scanners.scanners[i].beacons;
    total_sum += beacons_1.size();

    for (std::size_t j = 0; j < scanners.scanners.size(); ++j) {
      if (i == j) {
        continue;
      }
      const auto &beacons_2 = scanners.scanners[j].beacons;
      auto overlap =
          find_region(transformations, i, beacons_1, mappings, j, beacons_2);
      std::cout << "region done" << std::endl;
    }
  }

  std::vector<Beacon> relative_zero;
  std::vector<Beacon> scanner_pos_zero;
  std::vector<std::size_t> stack;

  if (mappings.size() > 0 && mappings.contains(0)) {

    std::vector<std::tuple<Axis, Axis, Axis>> trf_stack;
    Beacon offset{0, 0, 0};
    std::set<std::size_t> visited;

    dfs(0, mappings, offset, trf_stack, visited, relative_zero, scanners,
        scanner_pos_zero);
  }

  std::unordered_set<Beacon> unique_beacons(relative_zero.begin(),
                                            relative_zero.end());
  std::unordered_set<Beacon> unique_scanner(scanner_pos_zero.begin(),
                                            scanner_pos_zero.end());

  std::int64_t max_dist{0};
  for (auto const &beacon_1 : unique_scanner) {
    for (auto const &beacon_2 : unique_scanner) {
      max_dist = std::max(max_dist, std::abs(beacon_1.x - beacon_2.x) +
                                        std::abs(beacon_1.y - beacon_2.y) +
                                        std::abs(beacon_1.z - beacon_2.z));
    }
  }

  return {unique_beacons.size(), max_dist};
}
