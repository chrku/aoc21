#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "common.h"

struct Input {
    std::string initial;
    std::unordered_map<std::string, std::string> rules;

    Input(std::string initial, std::unordered_map<std::string, std::string> rules);

    static Input parseInput(const std::vector<std::string>& input);
};

std::string expand(const std::string& current, std::unordered_map<std::string, std::string>& rules);

std::unordered_map<std::string, uint64_t> expand_2(const std::unordered_map<std::string, uint64_t>& current,
                                              std::unordered_map<std::string, std::string>& rules,
                                              std::unordered_map<char, uint64_t>& freq_map);

int day14_part1(const std::vector<std::string>& input);

uint64_t day14_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
