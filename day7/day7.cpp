#include "day7.h"
#include <iostream>
#include <numeric>

std::vector<int> get_input(const std::vector<std::string>& input) {
    std::vector<int> ret_val;
    const auto nums = splitString(input[0], ",");
    std::transform(nums.begin(), nums.end(), std::back_inserter(ret_val),
                   [](const std::string& s) { return std::stoi(s); });
    return ret_val;
}

int median(const std::vector<int>& numbers) {
    if (numbers.size() % 2 == 1) {
        return numbers[numbers.size() / 2];
    } else {
        auto mid_1 = numbers[numbers.size() / 2];
        auto mid_2 = numbers[numbers.size() / 2 + 1];
        auto median = (1.0 / 2.0) * (mid_1 + mid_2);
        auto dist_1 = std::abs(mid_1 - median);
        auto dist_2 = std::abs(mid_2 - median);
        return (dist_1 > dist_2) ? mid_2 : mid_1;
    }
}

int day7_part1(const std::vector<std::string>& input) {
    auto numbers = get_input(input);
    std::sort(numbers.begin(), numbers.end());
    int cheapest = median(numbers);
    return std::accumulate(numbers.begin(), numbers.end(), 0, [=](int acc, int next) {
        return acc + std::abs(cheapest - next);
    });
}

int day7_part2(const std::vector<std::string>& input) {
    auto numbers = get_input(input);
    int cheapest = std::numeric_limits<int>::max();
    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.begin(), numbers.end());
    for (int num = min; num <= max; ++num) {
        int candidate = std::accumulate(numbers.begin(), numbers.end(), 0, [=](int acc, int next) {
            return acc + (std::abs(num - next) * (std::abs(num - next) + 1)) / 2;
        });
        if (candidate < cheapest) {
            cheapest = candidate;
        }
    }

    return cheapest;
}

