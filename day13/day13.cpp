
#include "day13.h"

#include <utility>
#include <iostream>

std::unordered_set<Point2i> fold(const std::unordered_set<Point2i>& points, FoldInstruction instr) {
    std::unordered_set<Point2i> new_set;

    for (const auto& point : points) {
        if (instr.direction == FoldDirection::VERTICAL) {
            if (point.x > instr.location) {
                new_set.emplace(instr.location - (point.x - instr.location), point.y);
            } else {
                new_set.insert(point);
            }
        } else {
            if (point.y > instr.location) {
                new_set.emplace(point.x, instr.location - (point.y - instr.location));
            } else {
                new_set.insert(point);
            }
        }
    }

    return new_set;
}

int day13_part1(const std::vector<std::string>& input) {
    auto parsed_input = Input::getInput(input);
    const auto& fold_instr = parsed_input.instructions[0];

    std::unordered_set<Point2i> point_set;
    for (const auto& point : parsed_input.points) {
        point_set.insert(point);
    }

    const auto fold_result = fold(point_set, fold_instr);

    return fold_result.size();
}

int day13_part2(const std::vector<std::string>& input) {
    auto parsed_input = Input::getInput(input);

    std::unordered_set<Point2i> point_set;
    for (const auto& point : parsed_input.points) {
        point_set.insert(point);
    }

    for (const auto& fold_instr : parsed_input.instructions) {
        point_set = fold(point_set, fold_instr);
    }

    auto max_x = *std::max_element(point_set.begin(), point_set.end(),
                                 [](const auto& p1, const auto& p2){ return p1.x < p2.x; });
    auto max_y = *std::max_element(point_set.begin(), point_set.end(),
                                   [](const auto& p1, const auto& p2){ return p1.y < p2.y; });

    for (int i = 0; i <= max_y.y; ++i) {
        for (int j = 0; j <= max_x.x; ++j) {
            if (point_set.count(Point2i(j, i))) {
                std::cout << "█";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    return point_set.size();
}

FoldInstruction::FoldInstruction(FoldDirection direction, int location)
    : direction(direction), location(location)
{}

Input::Input(std::vector<Point2i> points, std::vector<FoldInstruction> instructions)
    : points(std::move(points)), instructions(std::move(instructions))
{}

Input Input::getInput(const std::vector<std::string>& input) {
    int line_index = 0;
    std::vector<Point2i> points;

    while (line_index < input.size()) {
        const auto& cur_line = input[line_index];

        if (cur_line.empty()) {
            ++line_index;
            break;
        }

        auto coords = splitString(cur_line, ",");
        points.emplace_back(std::stoi(coords[0]), std::stoi(coords[1]));
        ++line_index;
    }

    std::vector<FoldInstruction> fold_instructions;

    while (line_index < input.size()) {
        const auto& cur_line = input[line_index];

        auto parts = splitString(cur_line, " ");
        const auto& fold_info = parts[2];
        const auto fold_parts = splitString(fold_info, "=");

        const auto fold_dir = (fold_parts[0] == "y") ? FoldDirection::HORIZONTAL : FoldDirection::VERTICAL;
        const auto fold_loc = std::stoi(fold_parts[1]);
        fold_instructions.emplace_back(fold_dir, fold_loc);

        ++line_index;
    }

    return {std::move(points), std::move(fold_instructions)};
}

