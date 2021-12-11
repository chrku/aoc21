#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>

#include "common.h"

std::vector<std::vector<int>> get_input(const std::vector<std::string>& input);

void increment(std::vector<std::vector<int>>& map);

int flash(std::vector<std::vector<int>>& map);

std::vector<Point2i> find_flash_points(const std::vector<std::vector<int>>& map);

int day11_part1(const std::vector<std::string>& input);

int day11_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
