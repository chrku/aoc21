#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>

#include "common.h"

std::vector<std::vector<int>> get_input(const std::vector<std::string>& input);

std::vector<Point2i> find_low_points(const std::vector<std::vector<int>>& height_map);

int day9_part1(const std::vector<std::string>& input);

int day9_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
