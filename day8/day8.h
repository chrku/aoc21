#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>

#include "common.h"

std::unordered_map<int, std::set<int>> get_digit_map();

std::unordered_map<int, std::set<char>> get_chars_digit();

std::unordered_map<std::string, int> get_digit_chars();

std::unordered_map<char, std::set<char>> get_decoding_map();

std::unordered_map<char, char> get_consistency_map(std::unordered_map<char, std::set<char>>& candidates);

std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>>
        get_input(const std::vector<std::string>& input);

int day8_part1(const std::vector<std::string>& input);

int day8_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
