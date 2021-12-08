#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <string>
#include <array>

constexpr int BOARD_SIZE = 5;
using BoardRow = std::array<int, BOARD_SIZE>;
using Board = std::array<BoardRow, BOARD_SIZE>;
using MarkRow = std::array<bool, BOARD_SIZE>;
using Marks = std::array<MarkRow, BOARD_SIZE>;

struct BingoInput {

    BingoInput(std::vector<Board> boards, std::vector<Marks> marks, std::vector<int> calledNumbers);

    std::vector<Board> boards;
    std::vector<Marks> marks;
    std::vector<int> calledNumbers;
    std::vector<bool> hasWon;
};

BingoInput parse_input(const std::vector<std::string>& input);

int day4_part1(const std::vector<std::string>& input);

int day4_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
