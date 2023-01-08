
#include "day21.h"
#include "common.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <unordered_set>
#include <utility>

int DeterministicDice::roll() {
  int ret_val = state;
  state = (state + 1) % 100;
  return ret_val;
}

Board::Board(std::unique_ptr<Dice> dice, int player1Position,
             int player2Position)
    : dice(std::move(dice)), player1Position(player1Position - 1),
      player2Position(player2Position - 1) {}

void Board::playerOneMove() {
  int result = dice->roll() + dice->roll() + dice->roll();
  numDiceRolls += 3;

  player1Position = ((player1Position + result) % 10);
  player1Score += player1Position + 1;
  if (player1Score >= 1000 && currentOutcome == Outcome::CONTINUE) {
    currentOutcome = Outcome::PLAYER_1_WIN;
  }
}

void Board::playerTwoMove() {
  int result = dice->roll() + dice->roll() + dice->roll();
  numDiceRolls += 3;

  player2Position = ((player2Position + result) % 10);
  player2Score += player2Position + 1;
  if (player2Score >= 1000 && currentOutcome == Outcome::CONTINUE) {
    currentOutcome = Outcome::PLAYER_2_WIN;
  }
}

Outcome Board::getCurrentOutcome() const { return currentOutcome; }

int Board::getPlayer1Score() const { return player1Score; }
int Board::getPlayer2Score() const { return player2Score; }
int Board::getNumDiceRolls() const { return numDiceRolls; }

int day21_part1(int player1Position, int player2Position) {
  std::unique_ptr<Dice> dice = std::make_unique<DeterministicDice>();
  Board board{std::move(dice), player1Position, player2Position};

  while (board.getCurrentOutcome() == Outcome::CONTINUE) {
    board.playerOneMove();
    if (board.getCurrentOutcome() == Outcome::PLAYER_1_WIN) {
      return board.getNumDiceRolls() * board.getPlayer2Score();
    }
    board.playerTwoMove();
    if (board.getCurrentOutcome() == Outcome::PLAYER_2_WIN) {
      return board.getNumDiceRolls() * board.getPlayer1Score();
    }
  }

  return 0;
}

std::pair<std::uint64_t, std::uint64_t>
numWins(std::unordered_map<std::tuple<int, int, int, int, bool>,
                           std::pair<std::uint64_t, std::uint64_t>> &memo,
        int player1Score, int player1Pos, int player2Score, int player2Pos,
        bool player1Turn) {
  auto arg_tuple = std::make_tuple(player1Score, player1Pos, player2Score,
                                   player2Pos, player1Turn);
  if (memo.contains(arg_tuple)) {
    return memo[arg_tuple];
  }

  if (player1Score >= 21 && !player1Turn) {
    if (!memo.contains(arg_tuple)) {
      memo[arg_tuple] = {0, 0};
    }
    memo[arg_tuple].first += 1;
    return memo[arg_tuple];
  }

  if (player2Score >= 21 && player1Turn) {
    if (!memo.contains(arg_tuple)) {
      memo[arg_tuple] = {0, 0};
    }
    memo[arg_tuple].second += 1;
    return memo[arg_tuple];
  }

  auto wins = std::make_pair<std::uint64_t, std::uint64_t>(0, 0);

  if (player1Turn) {
    for (int i = 1; i <= 3; ++i) {
      for (int j = 1; j <= 3; ++j) {
        for (int k = 1; k <= 3; ++k) {
          auto new_pos = ((player1Pos + i + j + k) % 10);
          auto new_score = player1Score + new_pos + 1;
          auto result = numWins(memo, new_score, new_pos, player2Score,
                                player2Pos, !player1Turn);
          wins.first += result.first;
          wins.second += result.second;
        }
      }
    }
  } else {
    for (int i = 1; i <= 3; ++i) {
      for (int j = 1; j <= 3; ++j) {
        for (int k = 1; k <= 3; ++k) {
          auto new_pos = ((player2Pos + i + j + k) % 10);
          auto new_score = player2Score + new_pos + 1;
          auto result = numWins(memo, player1Score, player1Pos, new_score,
                                new_pos, !player1Turn);
          wins.first += result.first;
          wins.second += result.second;
        }
      }
    }
  }

  if (!memo.contains(arg_tuple)) {
    memo[arg_tuple] = {0, 0};
  }

  memo[arg_tuple].first += wins.first;
  memo[arg_tuple].second += wins.second;

  return wins;
}

std::uint64_t day21_part2(int player1Position, int player2Position) {
  std::unordered_map<std::tuple<int, int, int, int, bool>,
                     std::pair<std::uint64_t, std::uint64_t>>
      memo;
  auto wins =
      numWins(memo, 0, player1Position - 1, 0, player2Position - 1, true);
  return std::max(wins.first, wins.second);
}
