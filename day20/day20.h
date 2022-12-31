#ifndef AOC_DAY20_H
#define AOC_DAY20_H

#include <functional>
#include <ostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.h"

class TranslationTable {
  std::vector<char> table;

public:
  TranslationTable(std::vector<char> table);
  static TranslationTable fromString(const std::string &str);
  char get(std::size_t index) const;
};

struct Grid {
  std::vector<char> underlying;
  std::size_t numRows;
  std::size_t numCols;

public:
  Grid(std::vector<char> underlying, std::size_t numRows, std::size_t numCols);
  static Grid fromInput(const std::vector<std::string> &input);
  static Grid empty(std::size_t numCols, std::size_t numRows);
  char get(std::size_t x, std::size_t y) const;
  void set(std::size_t x, std::size_t y, char c);
  Grid pad(std::size_t xPad, std::size_t yPad) const;

  std::size_t getNumSet() const;

  std::size_t rows() const { return numRows; }
  std::size_t cols() const { return numCols; }

};

std::ostream &operator<<(std::ostream &os, const Grid &grid);

struct Input {
  TranslationTable table;
  Grid grid;

  static Input parse(const std::vector<std::string> &input);
};

int day20_part1(const std::vector<std::string> &input);

int day20_part2(const std::vector<std::string> &input);

#endif // AOC_DAY20_H
