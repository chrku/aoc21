#include "day8.h"
#include <numeric>
#include <unordered_set>
#include <iostream>

std::unordered_map<int, std::set<int>> get_digit_map() {
    return {
            {2, {1}},
            {3, {7}},
            {4, {4}},
            {5, {2, 3, 5}},
            {6, {0, 6, 9}},
            {7, {8}}
    };
}

std::unordered_map<int, std::set<char>> get_chars_digit() {
    return {
            {0, {'a', 'b', 'c', 'e', 'f', 'g'}},
            {1, {'c', 'f'}},
            {2, {'a', 'c', 'd', 'e', 'g'}},
            {3, {'a', 'c', 'd', 'f', 'g'}},
            {4, {'b', 'c', 'd', 'f'}},
            {5, {'a', 'b', 'd', 'f', 'g'}},
            {6, {'a', 'b', 'd', 'e', 'f', 'g'}},
            {7, {'a', 'c', 'f'}},
            {8, {'a', 'b', 'c', 'd', 'e', 'f', 'g'}},
            {9, {'a', 'b', 'c', 'd', 'f', 'g'}}
    };
}

std::unordered_map<std::string, int> get_digit_chars() {
    return {
            {{'a', 'b', 'c', 'e', 'f', 'g'}, 0},
            {{'c', 'f'}, 1},
            {{'a', 'c', 'd', 'e', 'g'}, 2},
            {{'a', 'c', 'd', 'f', 'g'}, 3},
            {{'b', 'c', 'd', 'f'}, 4},
            {{'a', 'b', 'd', 'f', 'g'}, 5},
            {{'a', 'b', 'd', 'e', 'f', 'g'}, 6},
            {{'a', 'c', 'f'}, 7},
            {{'a', 'b', 'c', 'd', 'e', 'f', 'g'}, 8},
            {{'a', 'b', 'c', 'd', 'f', 'g'}, 9}
    };
}

std::unordered_map<char, std::set<char>> get_decoding_map() {
    return {
            {'a', {'a', 'b', 'c', 'd', 'e', 'f', 'g'}},
            {'b', {'a', 'b', 'c', 'd', 'e', 'f', 'g'}},
            {'c', {'a', 'b', 'c', 'd', 'e', 'f', 'g'}},
            {'d', {'a', 'b', 'c', 'd', 'e', 'f', 'g'}},
            {'e', {'a', 'b', 'c', 'd', 'e', 'f', 'g'}},
            {'f', {'a', 'b', 'c', 'd', 'e', 'f', 'g'}},
            {'g', {'a', 'b', 'c', 'd', 'e', 'f', 'g'}}
    };
}


std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>>
 get_input(const std::vector<std::string>& input) {
    std::vector<std::vector<std::string>> digits;
    std::vector<std::vector<std::string>> encoded;
    for (const auto& str : input) {
        const auto strs = splitString(str, "|");
        const auto digit = splitString(strs[0], " ");
        const auto encrypted = splitString(strs[1], " ");
        digits.push_back(digit);
        encoded.push_back(encrypted);
    }

    return std::make_pair(digits, encoded);
}

bool backtrack(std::vector<std::string>& digits,
               std::unordered_map<int, std::set<int>>& candidates,
               std::unordered_map<char, std::set<char>>& candidate_map,
               std::unordered_map<int, std::set<char>>& char_map,
               int digit_index) {
    if (digit_index >= digits.size()) {
        return true;
    }

    const auto& digit = digits[digit_index];
    auto len = digit.length();

    auto& cand = candidates[len];
    auto cand_copy = candidates[len];

    for (const auto candidate : cand_copy) {
        const auto& segments_for_candidate = char_map[candidate];
        auto cur_candidate_map = candidate_map;
        bool cand_works = true;

        for (char c : digit) {
            const auto cur_candidates = candidate_map[c];
            std::set<char> intersect;
            std::set_intersection(segments_for_candidate.begin(),
                                  segments_for_candidate.end(),
                                  cur_candidates.begin(),
                                  cur_candidates.end(),
                                  std::inserter(intersect, intersect.begin()));
            if (intersect.empty()) {
                candidate_map = cur_candidate_map;
                cand_works = false;
                break;
            } else {
                candidate_map[c] = intersect;
            }
        }


        if (cand_works) {
            cand.erase(candidate);
            if (!backtrack(digits, candidates, candidate_map, char_map, digit_index + 1)) {
                cand.insert(candidate);
                candidate_map = cur_candidate_map;
            } else {
                return true;
            }
        }
    }

    return false;
}

std::unordered_map<char, char> get_consistency_map(std::unordered_map<char, std::set<char>>& candidates) {
    std::unordered_map<char, char> flipped;
    for (const auto& pair : candidates) {
        if (pair.second.size() == 1) {
            flipped[*pair.second.begin()] = pair.first;
        }
    }

    while (flipped.size() != 7) {
        for (const auto &pair: candidates) {
            if (pair.second.size() > 1) {
                auto set = pair.second;
                for (const auto &possible: pair.second) {
                    if (flipped.count(possible)) {
                        set.erase(possible);
                    }
                }

                if (set.size() == 1) {
                    flipped[*set.begin()] = pair.first;
                }
            }
        }
    }

    std::unordered_map<char, char> ret_val;
    for (const auto& pair : flipped) {
        ret_val[pair.second] = pair.first;
    }

    return ret_val;
}

int day8_part1(const std::vector<std::string>& input) {
    auto inp = get_input(input);
    const auto& digits = inp.first;
    auto& encoded = inp.second;

    int num_unique = 0;
    for (const auto& sequence : encoded) {
        for (const auto& digit : sequence) {
            int len = digit.length();
            if (len == 2 || len == 3 || len == 4 || len == 7) {
                ++num_unique;
            }
        }
    }

    return num_unique;
}

int day8_part2(const std::vector<std::string>& input) {
    auto inp = get_input(input);
    auto& digits = inp.first;
    auto& encoded = inp.second;

    auto char_map = get_chars_digit();
    auto digit_map = get_digit_chars();

    std::unordered_set<char> base_set{'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    int sum = 0;

    for (int i = 0; i < digits.size(); ++i) {
        std::vector<std::string>& cur_digits = digits[i];
        const auto& cur_encoded = encoded[i];

        auto candidate_map = get_decoding_map();
        auto len_map = get_digit_map();
        backtrack(cur_digits, len_map, candidate_map, char_map, 0);
        auto decoder = get_consistency_map(candidate_map);

        int cur_num = 0;
        int cur_mult = std::pow(10, cur_encoded.size() - 1);
        for (const auto& code : cur_encoded) {
            std::vector<char> c;
            std::transform(code.begin(), code.end(), std::back_inserter(c),
                           [&](const char c) { return decoder[c]; });
            std::sort(c.begin(), c.end());
            std::string dig(c.begin(), c.end());
            int cur_digit = digit_map[dig];
            cur_num += cur_digit * cur_mult;
            cur_mult /= 10;
        }

        sum += cur_num;
    }

    return sum;
}

