#include "day6.h"
#include <iostream>
#include <numeric>

void transition_function(std::vector<int>& lanternfish) {
    auto orig_size = lanternfish.size();
    for (std::size_t i = 0; i < orig_size; ++i) {
        const auto& cur_fish = lanternfish[i];
        if (cur_fish == 0) {
            lanternfish.push_back(8);
            lanternfish[i] = 6;
        } else {
            --lanternfish[i];
        }
    }
}

std::vector<uint64_t> transition_function_improved(const std::vector<uint64_t>& lanternfish) {
    std::vector<uint64_t> ret_val(lanternfish.size(), 0);
    for (std::size_t i = 0; i < lanternfish.size(); ++i) {
        if (i == 0) {
            ret_val[8] += lanternfish[0];
            ret_val[6] += lanternfish[0];
        } else {
            ret_val[i - 1] += lanternfish[i];
        }
    }

    return ret_val;
}

int day6_part1(const std::vector<std::string>& input) {
    constexpr int NUM_DAYS = 80;

    std::vector<int> initial_state;
    auto nums = splitString(input[0], ",");
    std::transform(nums.begin(), nums.end(), std::back_inserter(initial_state),
                   [](const std::string& s) { return std::stoi(s); });

    for (int i = 0; i < NUM_DAYS; ++i) {
        transition_function(initial_state);
    }

    return static_cast<int>(initial_state.size());
}

uint64_t day6_part2(const std::vector<std::string>& input) {
    constexpr int NUM_DAYS = 256;
    constexpr int NUM_BUCKETS = 9;

    std::vector<int> initial_state;
    auto nums = splitString(input[0], ",");
    std::transform(nums.begin(), nums.end(), std::back_inserter(initial_state),
                   [](const std::string& s) { return std::stoi(s); });
    std::vector<uint64_t> state(NUM_BUCKETS, 0);

    for (const auto i : initial_state) {
        state[i] += 1;
    }

    for (int i = 0; i < NUM_DAYS; ++i) {
        state = transition_function_improved(state);
        std::cout << i << std::endl;
    }

    uint64_t ret = 0;
    for (const auto num : state) {
        ret += num;
    }
    return ret;
}

