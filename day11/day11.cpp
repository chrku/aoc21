#include "day11.h"
#include <numeric>
#include <queue>
#include <unordered_set>

std::vector<std::vector<int>> get_input(const std::vector<std::string>& input) {
    std::vector<std::vector<int>> ret_val;
    for (const std::string& line : input) {
        std::vector<int> row;
        std::transform(line.begin(), line.end(), std::back_inserter(row),
                       [](const char c) { return c - '0'; });
        ret_val.push_back(std::move(row));
    }

    return ret_val;
}

void increment(std::vector<std::vector<int>>& map) {
    for (auto& line : map) {
        std::for_each(line.begin(), line.end(),
                      [](int& i) { ++i; });
    }
}

std::vector<Point2i> find_flash_points(const std::vector<std::vector<int>>& map) {
    std::vector<Point2i> flash_points;

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] >= 10) {
                flash_points.emplace_back(j, i);
            }
        }
    }

    return flash_points;
}

int flash(std::vector<std::vector<int>>& map) {
    std::vector<Point2i> to_flash = find_flash_points(map);
    std::vector<Point2i> to_reset;
    std::unordered_set<Point2i> has_flashed;
    int total_flashed = 0;

    while (!to_flash.empty()) {
        auto cur_point = to_flash.back();
        to_flash.pop_back();

        if (!has_flashed.count(cur_point)) {
            auto neighbours = get_neighbours_8(cur_point.y, cur_point.x, map.size(), map[0].size());
            for (const auto &neighbour: neighbours) {
                ++map[neighbour.y][neighbour.x];
                if (map[neighbour.y][neighbour.x] >= 10 && !has_flashed.count(neighbour)) {
                    to_flash.push_back(neighbour);
                }
            }

            ++total_flashed;
            has_flashed.insert(cur_point);
            to_reset.push_back(cur_point);
        }
    }

    for (const auto& point: to_reset) {
        map[point.y][point.x] = 0;
    }

    return total_flashed;
}

int day11_part1(const std::vector<std::string>& input) {
    auto map = get_input(input);
    constexpr int num_steps = 100;

    int sum_flashed = 0;

    for (int step = 0; step < num_steps; ++step) {
        increment(map);
        auto num_flashed = flash(map);
        sum_flashed += num_flashed;
    }

    return sum_flashed;
}

int day11_part2(const std::vector<std::string>& input) {
    auto map = get_input(input);
    constexpr int num_steps = 1000000;

    for (int step = 0; step < num_steps; ++step) {
        increment(map);
        auto num_flashed = flash(map);
        if (num_flashed == 100) {
            return step + 1;
        }
    }

    return 0;
}

