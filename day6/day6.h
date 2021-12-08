#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>

#include "common.h"

void transition_function(std::vector<int>& lanternfish);

std::vector<uint64_t> transition_function_improved(const std::vector<uint64_t>& lanternfish);

int day6_part1(const std::vector<std::string>& input);

uint64_t day6_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
