#include "day2.h"
#include "common.h"

#include <algorithm>

int day2_part1(const std::vector<std::string>& input) {
    std::vector<std::vector<std::string>> pairs;
    std::transform(input.begin(), input.end(), std::back_inserter(pairs),
                   [](const std::string& s){ return splitString(s, " "); });

    int horizontal = 0;
    int vertical = 0;

    for (const auto& command : pairs) {
        const auto& direction = command[0];
        const int magnitude = std::stoi(command[1]);
        if (direction == "up") {
            vertical -= magnitude;
        } else if (direction == "down") {
            vertical += magnitude;
        } else if (direction == "forward") {
            horizontal += magnitude;
        }
    }

    return vertical * horizontal;
}

int day2_part2(const std::vector<std::string>& input) {
    std::vector<std::vector<std::string>> pairs;
    std::transform(input.begin(), input.end(), std::back_inserter(pairs),
                   [](const std::string& s){ return splitString(s, " "); });

    int horizontal = 0;
    int vertical = 0;
    int aim = 0;

    for (const auto& command : pairs) {
        const auto& direction = command[0];
        const int magnitude = std::stoi(command[1]);
        if (direction == "up") {
            aim -= magnitude;
        } else if (direction == "down") {
            aim += magnitude;
        } else if (direction == "forward") {
            horizontal += magnitude;
            vertical += magnitude * aim;
        }
    }

    return vertical * horizontal;
}
