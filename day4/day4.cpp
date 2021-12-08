#include "day4.h"
#include "common.h"

#include <algorithm>
#include <optional>

BingoInput parse_input(const std::vector<std::string>& input) {
    std::vector<int> called_numbers;
    std::vector<std::string> numbers_str = splitString(input[0], ",");
    std::vector<int> numbers;
    std::transform(numbers_str.begin(), numbers_str.end(), std::back_inserter(numbers),
                   [](const std::string& s) { return std::stoi(s); });

    std::vector<Board> boards;
    std::vector<Marks> marks;
    int i = 1;
    while (i < input.size()) {
        const std::string& line = input[i];
        if (line.empty()) {
            ++i;
            continue;
        }

        boards.push_back({});
        Board& b = boards.back();
        marks.push_back({});
        Marks& m = marks.back();

        auto it_board = b.begin();
        auto it_mark = m.begin();

        for (int j = 0; j < BOARD_SIZE; ++j, ++it_board, ++it_mark) {
            const std::string& cur_line = input[i + j];

            BoardRow row;
            std::vector<std::string> board_line = splitString(cur_line, " ");
            std::transform(board_line.begin(), board_line.end(), row.begin(),
                           [](const std::string& s) { return std::stoi(s); });
            *it_board = row;

            MarkRow mark_row;
            std::fill(mark_row.begin(), mark_row.end(), false);
            *it_mark = mark_row;
        }

        i += BOARD_SIZE;
    }

    return {std::move(boards), std::move(marks), std::move(numbers)};
}

bool check_row(const Marks& m, int row) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
        if (!m[row][j]) { return false; }
    }
    return true;
}

bool check_col(const Marks& m, int col) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (!m[i][col]) { return false; }
    }
    return true;
}

std::optional<std::pair<Board, Marks>> set_mark(BingoInput &b, int mark) {
    std::optional<std::pair<Board, Marks>> ret_val;
    for (int k = 0; k < b.boards.size(); ++k) {
        if (b.hasWon[k]) { continue; }
        auto& board = b.boards[k];
        auto& marks = b.marks[k];
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == mark) {
                    marks[i][j] = true;
                    if (check_col(marks, j) || check_row(marks, i)) {
                        b.hasWon[k] = true;
                        ret_val = std::make_pair(board, marks);
                    }
                }
            }
        }
    }
    return ret_val;
}

int get_sum(Board& b, Marks& m) {
    int sum = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (!m[i][j]) {
                sum += b[i][j];
            }
        }
    }
    return sum;
}

int day4_part1(const std::vector<std::string>& input) {
    BingoInput bingo = parse_input(input);
    for (auto number : bingo.calledNumbers) {
        auto result = set_mark(bingo, number);
        if (result.has_value()) {
            auto& val = result.value();
            auto& board = val.first;
            auto& marks = val.second;
            return number * get_sum(board, marks);
        }
    }
    return 0;
}

int day4_part2(const std::vector<std::string>& input) {
    BingoInput bingo = parse_input(input);
    int winningNumber = 0;
    for (auto number : bingo.calledNumbers) {
        auto result = set_mark(bingo, number);
        if (result.has_value()) {
            auto& val = result.value();
            auto& board = val.first;
            auto& marks = val.second;
            int sum = get_sum(board, marks);
            winningNumber = number * sum;
        }
    }
    return winningNumber;
}

BingoInput::BingoInput(std::vector<Board> boards, std::vector<Marks> marks, std::vector<int> calledNumbers)
    : boards(std::move(boards)), marks(std::move(marks)), calledNumbers(std::move(calledNumbers))
{
    for (const auto& _ : this->boards) {
        hasWon.push_back(false);
    }
}
