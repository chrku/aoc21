#ifndef AOC_DAY25_H
#define AOC_DAY25_H

#include <functional>
#include <limits>
#include <ostream>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.h"

struct Grid;

enum class GridCellType { EMPTY, CUCUMBER_RIGHT, CUCUMBER_DOWN };

struct GridCell {
  GridCellType type;
  std::size_t index;
};

struct Cucumber {
  bool attemptMove(const Grid &oldGrid, Grid &newGrid);

  enum class Direction { RIGHT, DOWN };

  Direction direction;
  Point2i position;
};

struct Grid {
  bool evolve();

  void setIndex(std::size_t row, std::size_t col, GridCell newCell);
  GridCell &get(std::size_t row, std::size_t col);
  const GridCell &get(std::size_t row, std::size_t col) const;

  std::string print() const;

  static Grid fromInput(const std::vector<std::string> &lines);

  std::size_t width;
  std::size_t height;

  std::vector<GridCell> cells;
  std::vector<Cucumber> rightCucumbers;
  std::vector<Cucumber> downCucumbers;
};

std::uint64_t day25_part1(const std::vector<std::string> &input);

std::uint64_t day25_part2(const std::vector<std::string> &input);

#endif // AOC_DAY25_H
