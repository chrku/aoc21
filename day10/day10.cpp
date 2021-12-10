#include "day10.h"
#include <numeric>
#include <queue>
#include <iostream>

std::unordered_map<char, int> get_cost_map() {
    return {
            {')', 3},
            {']', 57},
            {'}', 1197},
            {'>', 25137}
    };
}

std::unordered_map<char, int> get_cost_map_2() {
    return {
            {')', 1},
            {']', 2},
            {'}', 3},
            {'>', 4}
    };
}

std::unordered_map<char, char> get_paren_map() {
    return {
            {'(', ')'},
            {'[', ']'},
            {'{', '}'},
            {'<', '>'}
    };
}

int day10_part1(const std::vector<std::string>& input) {
    auto cost_map = get_cost_map();
    auto paren_map = get_paren_map();
    int sum = 0;

    for (const auto& line : input) {
        bool corrupted = false;
        int cost = 0;
        std::vector<char> stack;

        for (const char c : line) {
            if (c == '(' || c == '<' || c == '[' || c == '{') {
                stack.push_back(c);
            } else {
                if (stack.empty()) {
                    corrupted = false;
                    break;
                }
                if (paren_map[stack.back()] != c) {
                    cost = cost_map[c];
                    corrupted = true;
                    break;
                }

                stack.pop_back();
            }
        }

        if (corrupted) {
            sum += cost;
        }
    }

    return sum;
}

uint64_t day10_part2(const std::vector<std::string>& input) {
    auto cost_map = get_cost_map_2();
    auto paren_map = get_paren_map();
    std::vector<uint64_t> scores;

    for (const auto& line : input) {
        bool corrupted = false;
        std::vector<char> stack;

        for (const char c : line) {
            if (c == '(' || c == '<' || c == '[' || c == '{') {
                stack.push_back(c);
            } else {
                if (stack.empty()) {
                    corrupted = true;
                    break;
                }
                if (paren_map[stack.back()] != c) {
                    corrupted = true;
                    break;
                }

                stack.pop_back();
            }
        }

        if (!corrupted) {
            uint64_t score = 0;
            while (!stack.empty()) {
                score *= 5;
                score += cost_map[paren_map[stack.back()]];
                stack.pop_back();
            }
            scores.push_back(score);
        }
    }
    std::sort(scores.begin(), scores.end());

    return scores[scores.size() / 2];
}

