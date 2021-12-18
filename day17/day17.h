#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>

#include "common.h"

struct Input {
    Point2l lowerLeft;
    Point2l upperRight;

    Input(Point2l lower_left, Point2l upper_right);

    static Input get(const std::string& input);
};

std::int64_t day17_part1(const std::vector<std::string>& input);

std::int64_t day17_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
