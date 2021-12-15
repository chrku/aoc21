#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "common.h"

struct GridNode {
    Point2i loc;
    int priority;

    GridNode(const Point2i& loc, int priority) : loc(loc), priority(priority) {}
};

std::vector<std::vector<int>> get_input(const std::vector<std::string>& input);

std::int64_t shortest_path(std::vector<std::vector<int>> grid);

std::int64_t day15_part1(const std::vector<std::string>& input);

std::int64_t day15_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
