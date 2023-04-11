
#include "day25.h"
#include "common.h"

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <utility>

bool Cucumber::attemptMove(const Grid &oldGrid, Grid &newGrid) {
  Point2i newPosition{position};

  switch (direction) {
  case Direction::RIGHT:
    newPosition.x += 1;
    if (newPosition.x >= newGrid.width) {
      newPosition.x = 0;
    }
    break;
  case Direction::DOWN:
    newPosition.y += 1;
    if (newPosition.y >= newGrid.height) {
      newPosition.y = 0;
    }
    break;
  }

  if (oldGrid.get(newPosition.y, newPosition.x).type == GridCellType::EMPTY) {
    const GridCell &oldCell = oldGrid.get(position.y, position.x);
    GridCell toRemove{.type = GridCellType::EMPTY, .index = 0};
    GridCell toInsert{.type = direction == Direction::RIGHT
                                  ? GridCellType::CUCUMBER_RIGHT
                                  : GridCellType::CUCUMBER_DOWN,
                      .index = oldCell.index};

    newGrid.setIndex(position.y, position.x, toRemove);
    newGrid.setIndex(newPosition.y, newPosition.x, toInsert);
    position = newPosition;

    return true;
  }

  return false;
}

bool Grid::evolve() {
  bool anyHasMoved = false;
  Grid newGrid = *this;

  for (auto &cucumber : newGrid.rightCucumbers) {
    auto result = cucumber.attemptMove(*this, newGrid);
    anyHasMoved |= result;
  }

  *this = newGrid;
  newGrid = *this;

  for (auto &cucumber : newGrid.downCucumbers) {
    auto result = cucumber.attemptMove(*this, newGrid);
    anyHasMoved |= result;
  }

  *this = newGrid;

  return anyHasMoved;
}

void Grid::setIndex(std::size_t row, std::size_t col, GridCell newCell) {
  cells[row * width + col] = newCell;
}

GridCell &Grid::get(std::size_t row, std::size_t col) {
  return cells[row * width + col];
}

GridCell const &Grid::get(std::size_t row, std::size_t col) const {
  return cells[row * width + col];
}

std::string Grid::print() const {
  std::stringstream sstream;

  for (std::size_t i = 0; i < height; ++i) {
    for (std::size_t j = 0; j < width; ++j) {
      const GridCell &cell = get(i, j);

      switch (cell.type) {
      case GridCellType::EMPTY:
        sstream << ".";
        break;
      case GridCellType::CUCUMBER_DOWN:
        sstream << "v";
        break;
      case GridCellType::CUCUMBER_RIGHT:
        sstream << ">";
        break;
      }
    }
    sstream << '\n';
  }

  return sstream.str();
}

Grid Grid::fromInput(const std::vector<std::string> &lines) {
  std::vector<GridCell> cells;
  std::vector<Cucumber> rightCucumbers;
  std::vector<Cucumber> downCucumbers;

  auto width = std::accumulate(lines.begin(), lines.end(),
                               std::numeric_limits<std::size_t>::max(),
                               [](auto acc, const auto &s) {
                                 return std::min(acc, trim_copy(s).size());
                               });
  auto height = lines.size();

  int y = 0;
  for (const auto &line : lines) {
    int x = 0;
    for (const auto symbol : trim_copy(line)) {
      if (x >= width) {
        break;
      }

      if (symbol == '>') {
        rightCucumbers.push_back(
            {.direction = Cucumber::Direction::RIGHT, .position = {x, y}});
        cells.push_back({.type = GridCellType::CUCUMBER_RIGHT,
                         .index = rightCucumbers.size() - 1});
      } else if (symbol == 'v') {
        downCucumbers.push_back(
            {.direction = Cucumber::Direction::DOWN, .position = {x, y}});
        cells.push_back({.type = GridCellType::CUCUMBER_DOWN,
                         .index = downCucumbers.size() - 1});
      } else {
        cells.push_back({.type = GridCellType::EMPTY,
                         .index = std::numeric_limits<std::size_t>::max()});
      }

      x += 1;
    }
    y += 1;
  }

  return {width, height, cells, rightCucumbers, downCucumbers};
}

std::uint64_t day25_part1(const std::vector<std::string> &input) {
  auto grid = Grid::fromInput(input);
  auto steps = 0;
  std::cout << grid.print() << std::endl;
  while (grid.evolve()) {
    std::cout << grid.print() << std::endl;
    steps += 1;
  }
  return steps + 1;
}

std::uint64_t day25_part2(const std::vector<std::string> &input) { return 0; }