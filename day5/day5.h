#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>

#include "common.h"

enum class COORD_ACTION {
    NONE, INCREMENT, DECREMENT
};

Line2i read_line_segment(const std::string& input);

std::vector<Line2i> read_line_segments(const std::vector<std::string>& input);

int sum_raster(std::unordered_map<Point2i, int>& map);

void rasterize_line(Line2i line, std::unordered_map<Point2i,int>& map);

int day5_part1(const std::vector<std::string>& input);

int day5_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
