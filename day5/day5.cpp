#include <numeric>
#include "day5.h"

Line2i read_line_segment(const std::string& input) {
    auto seg = splitString(input, " ");
    const auto& begin = seg[0];
    const auto& end = seg[2];

    auto begin_split = splitString(begin, ",");
    auto end_split = splitString(end, ",");

    return {
            {std::stoi(begin_split[0]), std::stoi(begin_split[1])},
            {std::stoi(end_split[0]), std::stoi(end_split[1])}
    };
}

std::vector<Line2i> read_line_segments(const std::vector<std::string>& input) {
    std::vector<Line2i> ret_val;
    std::transform(input.begin(), input.end(), std::back_inserter(ret_val),
                   [](const std::string& s) { return read_line_segment(s); });
    return ret_val;
}

void rasterize_line(Line2i line, std::unordered_map<Point2i,int>& map) {
    auto x_action = COORD_ACTION::NONE;
    auto y_action = COORD_ACTION::NONE;

    if (line.begin.x < line.end.x) {
        x_action = COORD_ACTION::INCREMENT;
    } else if (line.begin.x > line.end.x) {
        x_action = COORD_ACTION::DECREMENT;
    }
    if (line.begin.y < line.end.y) {
        y_action = COORD_ACTION::INCREMENT;
    } else if (line.begin.y > line.end.y) {
        y_action = COORD_ACTION::DECREMENT;
    }

    while (line.begin.x != line.end.x || line.begin.y != line.end.y) {
        if (map.count(line.begin)) {
            ++map[line.begin];
        } else {
            map[line.begin] = 1;
        }

        switch (x_action) {
            case COORD_ACTION::NONE:
                break;
            case COORD_ACTION::INCREMENT:
                ++line.begin.x;
                break;
            case COORD_ACTION::DECREMENT:
                --line.begin.x;
                break;
        }
        switch (y_action) {
            case COORD_ACTION::NONE:
                break;
            case COORD_ACTION::INCREMENT:
                ++line.begin.y;
                break;
            case COORD_ACTION::DECREMENT:
                --line.begin.y;
                break;
        }
    }

    if (map.count(line.end)) {
        ++map[line.end];
    } else {
        map[line.end] = 1;
    }
}

int sum_raster(std::unordered_map<Point2i, int>& map) {
    return std::accumulate(map.begin(), map.end(), 0,
                           [](int current, const auto& entry)
                           { return current + (entry.second > 1 ? 1 : 0); });
}

int day5_part1(const std::vector<std::string>& input) {
    auto segments = read_line_segments(input);
    std::unordered_map<Point2i, int> raster;
    for (const auto& segment : segments) {
        if (segment.begin.x == segment.end.x || segment.begin.y == segment.end.y) {
            rasterize_line(segment, raster);
        }
    }
    return sum_raster(raster);
}

int day5_part2(const std::vector<std::string>& input) {
    auto segments = read_line_segments(input);
    std::unordered_map<Point2i, int> raster;
    for (const auto& segment : segments) {
        rasterize_line(segment, raster);
    }
    return sum_raster(raster);
}

