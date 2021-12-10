#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>

#include "common.h"

std::unordered_map<char, int> get_cost_map();

std::unordered_map<char, int> get_cost_map_2();

std::unordered_map<char, char> get_paren_map();

int day10_part1(const std::vector<std::string>& input);

uint64_t day10_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
