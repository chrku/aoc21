
#include "day15.h"

#include <utility>
#include <iostream>
#include <queue>
#include <array>

std::vector<std::vector<int>> get_input(const std::vector<std::string>& input) {
    std::vector<std::vector<int>> ret_val;

    for (const auto& line : input) {
        std::vector<int> row;
        std::transform(line.begin(), line.end(), std::back_inserter(row),
                       [](const char c) { return c - '0'; });
        ret_val.push_back(std::move(row));
    }

    return ret_val;
}

std::int64_t shortest_path(std::vector<std::vector<int>> grid) {
    std::unordered_set<Point2i> visited;

    auto cmp = [](const GridNode& g1, const GridNode& g2) {
        return g1.priority > g2.priority;
    };
    std::priority_queue<GridNode, std::vector<GridNode>, decltype(cmp)> to_visit(cmp);

    std::vector<std::vector<std::int64_t>> costs;

    for (std::size_t i = 0; i < grid.size(); ++i) {
        costs.emplace_back();
        for (std::size_t j = 0; j < grid[i].size(); ++j) {
            costs[i].push_back(std::numeric_limits<std::int64_t>::max());
        }
    }
    costs[0][0] = 0;

    GridNode start{{0, 0}, 0};
    to_visit.push(start);

    std::array<int, 4> dx{0, -1, 0, 1};
    std::array<int, 4> dy{-1, 0, 1, 0};

    while (!to_visit.empty()) {
        auto cur_node = to_visit.top();
        to_visit.pop();

        if (visited.count(cur_node.loc)) { continue; }

        for (int i = 0; i < dx.size(); ++i) {

            int offset_x = dx[i];
            int offset_y = dy[i];

            int row = cur_node.loc.y + offset_y;
            int col = cur_node.loc.x + offset_x;

            if (row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size()) {
                int new_dist = cur_node.priority + grid[row][col];
                if (new_dist < costs[row][col]) {
                    costs[row][col] = new_dist;
                    to_visit.push(GridNode({col, row}, new_dist));
                }
            }
        }

        visited.insert(cur_node.loc);
    }

    return costs[costs.size() - 1][costs[costs.size() - 1].size() - 1];
}

std::int64_t day15_part1(const std::vector<std::string>& input) {
    auto parsed = get_input(input);
    return shortest_path(parsed);
}

std::int64_t day15_part2(const std::vector<std::string>& input) {
    auto parsed = get_input(input);

    auto num_rows = parsed.size();
    auto num_cols = parsed[0].size();

    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < 4 * num_cols; ++j) {
            int val = parsed[i][j % num_rows] + (1 + j / num_cols);
            if (val > 9) { val = 1 + val % 10; }
            parsed[i].push_back(val);
        }
    }

    for (int i = 0; i < num_rows * 4; ++i) {
        parsed.emplace_back();
        for (int j = 0; j < 5 * num_cols; ++j) {
            int val = parsed[i % num_rows][j] + (1 + i / num_cols);
            if (val > 9) { val = 1 + val % 10; }
            parsed[i + num_rows].push_back(val);
        }
    }

    return shortest_path(parsed);
}
