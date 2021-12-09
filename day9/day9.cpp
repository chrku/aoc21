#include "day9.h"
#include <numeric>
#include <queue>
#include <unordered_set>

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

std::vector<Point2i> find_low_points(const std::vector<std::vector<int>>& height_map) {
    std::vector<Point2i> low_points;
    for (int i = 0; i < height_map.size(); ++i) {
        for (int j = 0; j < height_map[i].size(); ++j) {
            auto cur_element = height_map[i][j];
            bool is_smaller = true;

            if (i > 0) {
                auto up = height_map[i - 1][j];
                if (cur_element >= up) {
                    is_smaller = false;
                }
            }
            if (i < height_map.size() - 1) {
                auto down = height_map[i + 1][j];
                if (cur_element >= down) {
                    is_smaller = false;
                }
            }
            if (j > 0) {
                auto left = height_map[i][j - 1];
                if (cur_element >= left) {
                    is_smaller = false;
                }
            }
            if (j < height_map[i].size() - 1) {
                auto right = height_map[i][j + 1];
                if (cur_element >= right) {
                    is_smaller = false;
                }
            }

            if (is_smaller) {
                low_points.emplace_back(j, i);
            }
        }
    }

    return low_points;
}

int day9_part1(const std::vector<std::string>& input) {
    auto height_map = get_input(input);
    auto low_points = find_low_points(height_map);
    int sum = std::accumulate(low_points.begin(), low_points.end(), 0,
                              [&](const int acc, const auto& point)
                              { return acc + 1 + height_map[point.y][point.x]; });
    return sum;
}

int day9_part2(const std::vector<std::string>& input) {
    auto height_map = get_input(input);
    auto low_points = find_low_points(height_map);
    std::vector<int> basin_sizes;
    std::unordered_set<Point2i> visited;

    for (const auto& point : low_points) {
        std::queue<Point2i> basin_points;
        basin_points.push(point);
        int size = 0;

        while (!basin_points.empty()) {
            auto cur_point = basin_points.front();
            basin_points.pop();
            if (!visited.count(cur_point)) {
                size += 1;

                auto j = cur_point.x;
                auto i = cur_point.y;
                auto height = height_map[i][j];

                if (i > 0 && height_map[i - 1][j] != 9 && height_map[i - 1][j] >= height) {
                    basin_points.emplace(j, i - 1);
                }
                if (i < height_map.size() - 1 && height_map[i + 1][j] != 9 && height_map[i + 1][j] >= height) {
                    basin_points.emplace(j, i + 1);
                }
                if (j > 0 && height_map[i][j - 1] != 9 && height_map[i][j - 1] >= height) {
                    basin_points.emplace(j - 1, i);
                }
                if (j < height_map[i].size() - 1 && height_map[i][j + 1] != 9 && height_map[i][j + 1] >= height) {
                    basin_points.emplace(j + 1, i);
                }

                visited.insert(cur_point);
            }
        }

        basin_sizes.push_back(size);
    }

    std::sort(basin_sizes.begin(), basin_sizes.end());

    if (basin_sizes.size() > 3) {
        return basin_sizes[basin_sizes.size() - 1] *
        basin_sizes[basin_sizes.size() - 2] *
        basin_sizes[basin_sizes.size() - 3];
    }

    return 0;
}

