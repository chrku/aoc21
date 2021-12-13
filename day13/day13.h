#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "common.h"

enum class FoldDirection {
    VERTICAL, HORIZONTAL
};

struct FoldInstruction {
    FoldDirection direction;
    int location;

    FoldInstruction(FoldDirection direction, int location);
};

struct Input {
    std::vector<Point2i> points;
    std::vector<FoldInstruction> instructions;

    Input(std::vector<Point2i> points, std::vector<FoldInstruction> instructions);

    static Input getInput(const std::vector<std::string>& input);
};

std::unordered_set<Point2i> fold(const std::unordered_set<Point2i>& points, FoldInstruction instr);

int day13_part1(const std::vector<std::string>& input);

int day13_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
