#include "day1.h"

int day2_part1(const std::vector<std::string>& input) {
    int previous = 0;
    bool has_previous = false;
    int num_increases = 0;

    for (const auto& line : input) {
        int val = std::stoi(line);
        if (has_previous && val > previous) {
            ++num_increases;
        }

        previous = val;
        has_previous = true;
    }

    return num_increases;
}

int day2_part2(const std::vector<std::string>& input) {
    constexpr int num_sliding = 3;
    int previous = 0;
    bool has_previous = false;
    int num_increases = 0;

    for (int i = 0; i < input.size() - num_sliding + 1; ++i) {
        int val = 0;
        for (int j = 0; j < num_sliding; ++j) {
            val += std::stoi(input[i + j]);
        }

        if (has_previous && val > previous) {
            ++num_increases;
        }

        previous = val;
        has_previous = true;
    }

    return num_increases;
}
