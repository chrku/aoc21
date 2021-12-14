
#include "day14.h"

#include <utility>
#include <iostream>

std::string expand(const std::string& current, std::unordered_map<std::string, std::string>& rules) {
    std::string ret_val;

    for (int i = 0; i < current.size() - 1; ++i) {
        const auto cur_pair = current.substr(i, 2);
        ret_val.push_back(current[i]);
        if (rules.count(cur_pair)) {
            ret_val.append(rules[cur_pair]);
        }
    }

    ret_val.push_back(current.back());

    return ret_val;
}

std::unordered_map<std::string, uint64_t> expand_2(const std::unordered_map<std::string, uint64_t>& current,
                                              std::unordered_map<std::string, std::string>& rules,
                                              std::unordered_map<char, uint64_t>& freq_map) {
    std::unordered_map<std::string, uint64_t> next_map = current;

    for (const auto& pair : current) {
        const auto& str = pair.first;
        if (rules.count(str)) {
            const auto& rule = rules[str];
            const std::string new_first{str[0], rule[0]};
            const std::string new_second{rule[0], str[1]};
            next_map[new_first] += pair.second;
            next_map[new_second] += pair.second;
            next_map[str] -= pair.second;

            if (!freq_map.count(rule[0])) {
                freq_map[rule[0]] = pair.second;
            } else {
                freq_map[rule[0]] += pair.second;
            }
        }
    }

    return next_map;
}

int day14_part1(const std::vector<std::string>& input) {
    auto parsed_input = Input::parseInput(input);
    std::string& init = parsed_input.initial;
    for (int i = 0; i < 10; ++i) {
        init = expand(init, parsed_input.rules);
    }

    std::unordered_map<char, int> freq_map;
    for (char c : init) {
        if (!freq_map.count(c)) {
            freq_map[c] = 1;
        } else {
            ++freq_map[c];
        }
    }

    auto most_common = *std::max_element(freq_map.begin(), freq_map.end(),
                                        [](const auto &p1, const auto& p2) { return p1.second < p2.second; });
    auto least_common = *std::min_element(freq_map.begin(), freq_map.end(),
                                         [](const auto &p1, const auto& p2) { return p1.second < p2.second; });

    return most_common.second - least_common.second;
}

uint64_t day14_part2(const std::vector<std::string>& input) {
    auto parsed_input = Input::parseInput(input);
    std::string& init = parsed_input.initial;

    std::unordered_map<char, uint64_t> freq_map;
    for (char c : init) {
        if (!freq_map.count(c)) {
            freq_map[c] = 1;
        } else {
            ++freq_map[c];
        }
    }

    std::unordered_map<std::string, uint64_t> pair_map;
    for (int i = 0; i < init.size() - 1; ++i) {
        const auto sub = init.substr(i, 2);
        if (!pair_map.count(sub)) {
            pair_map[sub] = 1;
        } else {
            pair_map[sub] += 1;
        }
    }

    for (int i = 0; i < 40; ++i) {
        pair_map = expand_2(pair_map, parsed_input.rules, freq_map);
    }

    auto most_common = *std::max_element(freq_map.begin(), freq_map.end(),
                                         [](const auto &p1, const auto& p2) { return p1.second < p2.second; });
    auto least_common = *std::min_element(freq_map.begin(), freq_map.end(),
                                          [](const auto &p1, const auto& p2) { return p1.second < p2.second; });

    return most_common.second - least_common.second;
}

Input::Input(std::string initial, std::unordered_map<std::string, std::string> rules)
    : initial(std::move(initial)), rules(std::move(rules)) {}

Input Input::parseInput(const std::vector<std::string>& input) {
    int line_index = 0;

    std::string initial;
    while (line_index < input.size()) {
        const auto& str = input[line_index];
        if (str.empty()) {
            ++line_index;
            break;
        }

        initial = input[line_index];
        ++line_index;
    }

    std::unordered_map<std::string, std::string> rules;
    while (line_index < input.size()) {
        const auto& str = input[line_index];
        const auto parts = splitString(str, " -> ");
        rules[parts[0]] = parts[1];
        ++line_index;
    }

    return {std::move(initial), std::move(rules)};
}
