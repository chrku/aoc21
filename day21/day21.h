#ifndef AOC_DAY21_H
#define AOC_DAY21_H

#include <functional>
#include <ostream>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common.h"

class Dice {
public:
  virtual int roll() = 0;
  virtual ~Dice() = default;
};

class DeterministicDice : public Dice {
public:
  int roll() override;

private:
  int state{1};
};

enum class Outcome { CONTINUE, PLAYER_1_WIN, PLAYER_2_WIN };

class Board {
public:
  Board(std::unique_ptr<Dice> dice, int player1Position, int player2Position);

  void playerOneMove();
  void playerTwoMove();

  Outcome getCurrentOutcome() const;
  int getPlayer1Score() const;
  int getPlayer2Score() const;
  int getNumDiceRolls() const;

private:
  std::unique_ptr<Dice> dice;

  int player1Score{0};
  int player1Position{1};
  int player2Score{0};
  int player2Position{1};
  Outcome currentOutcome{Outcome::CONTINUE};

  int numDiceRolls{0};
};

// function has to live in the std namespace
// so that it is picked up by argument-dependent name lookup (ADL).
namespace std {
namespace {

// Code from boost
// Reciprocal of the golden ratio helps spread entropy
//     and handles duplicates.
// See Mike Seymour in magic-numbers-in-boosthash-combine:
//     https://stackoverflow.com/questions/4948780

template <class T> inline void hash_combine(std::size_t &seed, T const &v) {
  seed ^= hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

// Recursive template code derived from Matthieu M.
template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
  static void apply(size_t &seed, Tuple const &tuple) {
    HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
    hash_combine(seed, get<Index>(tuple));
  }
};

template <class Tuple> struct HashValueImpl<Tuple, 0> {
  static void apply(size_t &seed, Tuple const &tuple) {
    hash_combine(seed, get<0>(tuple));
  }
};
} // namespace

template <typename... TT> struct hash<std::tuple<TT...>> {
  size_t operator()(std::tuple<TT...> const &tt) const {
    size_t seed = 0;
    HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
    return seed;
  }
};
} // namespace std

int day21_part1(int player1Position, int player2Position);

std::uint64_t day21_part2(int player1Position, int player2Position);

#endif // AOC_DAY21_H
