#include "common.h"
#include "day25.h"
#include "gtest/gtest.h"

#include <fstream>

TEST(Day25Test, Test_1) {
  std::ifstream ifs("input/day25_test.txt");
  auto input = readInputLines(ifs);
  auto grid = Grid::fromInput(input);
  grid.evolve();
  EXPECT_EQ(R""(..vv>..
.......
>......
v.....>
>......
.......
....v..
)"",
            grid.print());
}

TEST(Day25Test, Test_2) {
  std::ifstream ifs("input/day25_test.txt");
  auto input = readInputLines(ifs);
  auto grid = Grid::fromInput(input);
  grid.evolve();
  grid.evolve();
  EXPECT_EQ(R""(....v>.
..vv...
.>.....
......>
v>.....
.......
.......
)"",
            grid.print());
}

TEST(Day25Test, Test_3) {
  std::ifstream ifs("input/day25_test.txt");
  auto input = readInputLines(ifs);
  auto grid = Grid::fromInput(input);
  grid.evolve();
  grid.evolve();
  grid.evolve();
  EXPECT_EQ(R""(......>
..v.v..
..>v...
>......
..>....
v......
.......
)"",
            grid.print());
}

TEST(Day25Test, Test_4) {
  std::ifstream ifs("input/day25_test.txt");
  auto input = readInputLines(ifs);
  auto grid = Grid::fromInput(input);
  grid.evolve();
  grid.evolve();
  grid.evolve();
  grid.evolve();
  EXPECT_EQ(R""(>......
..v....
..>.v..
.>.v...
...>...
.......
v......
)"",
            grid.print());
}

TEST(Day25Test, Test_5) {
  std::ifstream ifs("input/day25_test_1.txt");
  auto input = readInputLines(ifs);
  auto grid = Grid::fromInput(input);
  grid.evolve();
  EXPECT_EQ(R""(....>.>v.>
v.v>.>v.v.
>v>>..>v..
>>v>v>.>.v
.>v.v...v.
v>>.>vvv..
..v...>>..
vv...>>vv.
>.v.v..v.v
)"",
            grid.print());
}

TEST(Day25Test, Test_6) {
  std::ifstream ifs("input/day25_test_1.txt");
  auto input = readInputLines(ifs);
  auto grid = Grid::fromInput(input);
  grid.evolve();
  std::cout << grid.print() << std::endl;
  grid.evolve();
  std::cout << grid.print() << std::endl;

  EXPECT_EQ(R""(>.v.v>>..v
v.v.>>vv..
>v>.>.>.v.
>>v>v.>v>.
.>..v....v
.>v>>.v.v.
v....v>v>.
.vv..>>v..
v>.....vv.
)"",
            grid.print());
}

TEST(Day22Test, Test7) {
  std::ifstream ifs("input/day25_test_1.txt");
  auto result = day25_part1(readInputLines(ifs));
  EXPECT_EQ(result, 58);
}
