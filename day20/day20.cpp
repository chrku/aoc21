
#include "day20.h"
#include "common.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <utility>

TranslationTable TranslationTable::fromString(const std::string &str) {
  std::vector<char> ret_val;

  std::transform(str.begin(), str.end(), std::back_inserter(ret_val),
                 [](char c) { return c; });

  return {std::move(ret_val)};
}

TranslationTable::TranslationTable(std::vector<char> table)
    : table(std::move(table)) {}

char TranslationTable::get(std::size_t index) const { return table.at(index); }

Grid::Grid(std::vector<char> underlying, std::size_t numRows,
           std::size_t numCols)
    : underlying(std::move(underlying)), numRows(numRows), numCols(numCols) {}

Grid Grid::fromInput(const std::vector<std::string> &input) {
  std::vector<char> concat;
  std::size_t numCols = 0;
  std::size_t numRows = 0;

  for (const auto &line : input) {
    auto trimmed = trim_copy(line);
    if (!trimmed.empty()) {
      std::transform(trimmed.begin(), trimmed.end(), std::back_inserter(concat),
                     [](char c) { return c; });
    }

    numCols = trimmed.size();
    numRows++;
  }

  return {std::move(concat), numRows, numCols};
}

Grid Grid::empty(std::size_t numCols, std::size_t numRows) {
  return {std::vector<char>(numRows * numCols, '.'), numRows, numCols};
}

char Grid::get(std::size_t x, std::size_t y) const {
  return underlying.at(y * numCols + x);
}

void Grid::set(std::size_t x, std::size_t y, char c) {
  underlying[y * numCols + x] = c;
}

Grid Grid::pad(std::size_t xPad, std::size_t yPad) const {
  std::vector<char> new_grid;
  std::size_t new_width = numCols + 2 * xPad;
  std::size_t new_height = numRows + 2 * yPad;

  for (std::size_t i = 0; i < yPad; ++i) {
    for (std::size_t j = 0; j < new_width; ++j) {
      new_grid.push_back('.');
    }
  }

  for (std::size_t i = 0; i < numRows; ++i) {
    for (std::size_t j = 0; j < xPad; ++j) {
      new_grid.push_back('.');
    }

    for (std::size_t j = 0; j < numCols; ++j) {
      new_grid.push_back(get(j, i));
    }

    for (std::size_t j = 0; j < xPad; ++j) {
      new_grid.push_back('.');
    }
  }

  for (std::size_t i = 0; i < yPad; ++i) {
    for (std::size_t j = 0; j < new_width; ++j) {
      new_grid.push_back('.');
    }
  }

  return {new_grid, new_height, new_width};
}

std::ostream &operator<<(std::ostream &os, const Grid &grid) {
  for (std::size_t i = 0; i < grid.rows(); ++i) {
    for (std::size_t j = 0; j < grid.cols(); ++j) {
      os << grid.get(j, i);
    }
    os << '\n';
  }

  os << '\n';

  return os;
}

Input Input::parse(const std::vector<std::string> &input) {
  std::size_t index = 0;

  while (index < input.size()) {
    auto line = trim_copy(input[index]);
    if (!line.empty()) {
      break;
    }
    ++index;
  }

  auto tbl_string = trim_copy(input[index++]);
  TranslationTable table = TranslationTable::fromString(tbl_string);

  while (index < input.size()) {
    auto line = trim_copy(input[index]);
    if (!line.empty()) {
      break;
    }
    ++index;
  }

  std::vector<std::string> input_grid;
  while (index < input.size()) {
    auto line = trim_copy(input[index]);
    if (line.empty()) {
      break;
    }
    input_grid.push_back(line);
    ++index;
  }

  Grid grid = Grid::fromInput(input_grid);

  return {table, grid};
}

std::size_t Grid::getNumSet() const {
    std::size_t num_set = 0;

    for (std::size_t i = 0; i < numRows; ++i) {
        for (std::size_t j = 0; j < numCols; ++j) {
            if (get(j, i) == '#') {
                ++num_set;
            }
        }
    }

    return num_set;
}


Grid expand(const Grid &inputGrid, const TranslationTable &translationTable) {
  Grid result_grid = Grid::empty(inputGrid.rows() - 2, inputGrid.rows() - 2);

  for (std::size_t i = 1; i < inputGrid.rows() - 1; ++i) {
    for (std::size_t j = 1; j < inputGrid.cols() - 1; ++j) {
      std::size_t result_index = 0;
      std::size_t offset = 1 << 8;
      for (std::size_t k = i - 1; k <= i + 1; ++k) {
        for (std::size_t l = j - 1; l <= j + 1; ++l) {
          if (inputGrid.get(l, k) == '#') {
            result_index |= offset;
          }
          offset >>= 1;
        }
      }

      auto translated = translationTable.get(result_index);
      result_grid.set(j - 1, i - 1, translated);
    }
  }

  return result_grid;
}

int day20_part1(const std::vector<std::string> &input) {
  Input input_data = Input::parse(input);

  Grid current_grid = input_data.grid.pad(15, 15);
  for (std::size_t i = 0; i < 2; ++i) {
    current_grid = expand(current_grid, input_data.table);
  }

  return current_grid.getNumSet();
}

int day20_part2(const std::vector<std::string> &input) {
  Input input_data = Input::parse(input);

  Grid current_grid = input_data.grid.pad(300, 300);
  for (std::size_t i = 0; i < 50; ++i) {
    current_grid = expand(current_grid, input_data.table);
  }

  return current_grid.getNumSet();
}
