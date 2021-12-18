#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>

#include "common.h"

struct TreeNode : public std::enable_shared_from_this<TreeNode> {
    std::shared_ptr<TreeNode> parent;

    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    int leftVal = 0;
    int rightVal = 0;

    TreeNode();
    TreeNode(std::shared_ptr<TreeNode> parent, std::shared_ptr<TreeNode> left,
             std::shared_ptr<TreeNode> right);

    static std::shared_ptr<TreeNode> parseInput(const std::string& input);
    static std::shared_ptr<TreeNode> parseInput(const std::string& input, int& idx,
                                                std::shared_ptr<TreeNode> parent);
    [[nodiscard]] std::string toString() const;

    void reduce();

    bool explode(int depth);
    bool split();

    int magnitude() const;

    std::shared_ptr<TreeNode> copy(std::shared_ptr<TreeNode> parent) const;
};

std::shared_ptr<TreeNode> operator+(const std::shared_ptr<TreeNode>& lhs, const std::shared_ptr<TreeNode>& rhs);

std::int64_t day18_part1(const std::vector<std::string>& input);

std::int64_t day18_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
