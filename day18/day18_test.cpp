#include "gtest/gtest.h"
#include "day18.h"
#include "common.h"

#include <fstream>

TEST(Day18Test, ExplodeTest1) {
    auto tree = TreeNode::parseInput("[[[[[9,8],1],2],3],4]");
    tree->explode(0);
    EXPECT_EQ(tree->toString(), "[[[[0,9],2],3],4]");
}

TEST(Day18Test, ExplodeTest2) {
    auto tree = TreeNode::parseInput("[7,[6,[5,[4,[3,2]]]]]");
    tree->explode(0);
    EXPECT_EQ(tree->toString(), "[7,[6,[5,[7,0]]]]");
}

TEST(Day18Test, ExplodeTest3) {
    auto tree = TreeNode::parseInput("[[6,[5,[4,[3,2]]]],1]");
    tree->explode(0);
    EXPECT_EQ(tree->toString(), "[[6,[5,[7,0]]],3]");
}

TEST(Day18Test, ExplodeTest4) {
    auto tree = TreeNode::parseInput("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]");
    tree->explode(0);
    EXPECT_EQ(tree->toString(), "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");
}

TEST(Day18Test, AddTest1) {
    auto tree_1 = TreeNode::parseInput("[[[[4,3],4],4],[7,[[8,4],9]]]");
    auto tree_2 = TreeNode::parseInput("[1,1]");
    auto tree_3 = tree_1 + tree_2;
    EXPECT_EQ(tree_3->toString(), "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]");
}

TEST(Day18Test, AddTest2) {
    auto tree_1 = TreeNode::parseInput("[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]");
    auto tree_2 = TreeNode::parseInput("[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]");
    auto tree_3 = tree_1 + tree_2;
    EXPECT_EQ(tree_3->toString(), "[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]");
}

TEST(Day18Test, Test1) {
    std::ifstream ifs("input/day18_test.txt");
    auto val = day18_part1(readInputLines(ifs));
    EXPECT_EQ(val, 4140);
}

TEST(Day18Test, Test3) {
    std::ifstream ifs("input/day18_test.txt");
    auto val = day18_part2(readInputLines(ifs));
    EXPECT_EQ(val, 3993);
}
