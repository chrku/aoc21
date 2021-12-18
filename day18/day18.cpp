
#include "day18.h"

#include <utility>
#include <queue>
#include <numeric>
#include <iostream>

std::int64_t day18_part1(const std::vector<std::string>& input) {
    std::vector<std::shared_ptr<TreeNode>> numbers;
    std::transform(input.begin(), input.end(), std::back_inserter(numbers),
                   [](const std::string& s) { int idx = 0; return TreeNode::parseInput(s, idx, {}); });
    auto acc = numbers[0];
    auto sum = std::accumulate(numbers.begin() + 1, numbers.end(), acc);
    return sum->magnitude();
}

std::int64_t day18_part2(const std::vector<std::string>& input) {
    std::vector<std::shared_ptr<TreeNode>> numbers;
    std::transform(input.begin(), input.end(), std::back_inserter(numbers),
                   [](const std::string& s) { int idx = 0; return TreeNode::parseInput(s, idx, {}); });
    std::vector<int> magnitudes;
    for (int i = 0; i < numbers.size(); ++i) {
        for (int j = 0; j < numbers.size(); ++j) {
            if (i != j) {
                magnitudes.push_back((numbers[i] + numbers[j])->magnitude());
            }
        }
    }

    return *std::max_element(magnitudes.begin(), magnitudes.end());
}

TreeNode::TreeNode(std::shared_ptr<TreeNode> parent, std::shared_ptr<TreeNode> left,
                   std::shared_ptr<TreeNode> right) :
                   parent(std::move(parent)), left(std::move(left)), right(std::move(right)) {}

std::shared_ptr<TreeNode> TreeNode::parseInput(const std::string& input, int& idx,
                                               std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> current = std::make_shared<TreeNode>();
    current->parent = std::move(parent);

    char cur_char = input[idx];
    if (cur_char != '[') {
        throw std::runtime_error("Expected [");
    }

    ++idx;
    cur_char = input[idx];

    if (cur_char == '[') {
        auto left = parseInput(input, idx, current);
        current->left = left;
    } else if (std::isdigit(cur_char)) {
        std::string cur_num;
        while (std::isdigit(cur_char)) {
            cur_num.push_back(cur_char);
            ++idx;
            cur_char = input[idx];
        }

        current->leftVal = std::stoi(cur_num);
    }

    cur_char = input[idx];
    if (cur_char != ',') {
        throw std::runtime_error("Expected ,");
    }

    ++idx;
    cur_char = input[idx];
    if (cur_char == '[') {
        auto right = parseInput(input, idx, current);
        current->right = right;
    } else if (std::isdigit(cur_char)) {
        std::string cur_num;
        while (std::isdigit(cur_char)) {
            cur_num.push_back(cur_char);
            ++idx;
            cur_char = input[idx];
        }
        current->rightVal = std::stoi(cur_num);
    }

    cur_char = input[idx];
    if (cur_char != ']') {
        throw std::runtime_error("Expected ,");
    }
    ++idx;

    return current;
}

std::string TreeNode::toString() const {
    std::string ret_val;
    ret_val.push_back('[');

    if (this->left) {
        ret_val.append(left->toString());
    } else {
        ret_val.append(std::to_string(leftVal));
    }

    ret_val.push_back(',');

    if (this->right) {
        ret_val.append(right->toString());
    } else {
        ret_val.append(std::to_string(rightVal));
    }

    ret_val.push_back(']');

    return ret_val;
}

void TreeNode::reduce() {
    while (true) {
        bool changed = explode(0);
        if (changed) {
            continue;
        }
        changed = split();
        if (!changed) {
            break;
        } else {
            continue;
        }
    }
}

bool TreeNode::explode(int depth) {
    bool changed = false;

    if (!this->left && !this->right && depth == 4) {
        auto cur_ptr = shared_from_this();

        while (cur_ptr && cur_ptr->parent && !(cur_ptr == cur_ptr->parent->right)) {
            cur_ptr = cur_ptr->parent;
        }

        if (cur_ptr && cur_ptr->parent && cur_ptr == cur_ptr->parent->right) {
            cur_ptr = cur_ptr->parent;

            if (!cur_ptr->left) {
                cur_ptr->leftVal += this->leftVal;
            } else {
                cur_ptr = cur_ptr->left;
                while (cur_ptr->right) {
                    cur_ptr = cur_ptr->right;
                }
                cur_ptr->rightVal += this->leftVal;
            }
        }

        cur_ptr = shared_from_this();

        while (cur_ptr && cur_ptr->parent && !(cur_ptr == cur_ptr->parent->left)) {
            cur_ptr = cur_ptr->parent;
        }

        if (cur_ptr && cur_ptr->parent && cur_ptr == cur_ptr->parent->left) {
            cur_ptr = cur_ptr->parent;

            if (!cur_ptr->right) {
                cur_ptr->rightVal += this->rightVal;
            } else {
                cur_ptr = cur_ptr->right;
                while (cur_ptr->left) {
                    cur_ptr = cur_ptr->left;
                }
                cur_ptr->leftVal += this->rightVal;
            }
        }

        if (this == parent->left.get()) {
            parent->left = nullptr;
            parent->leftVal = 0;
        }
        if (this == parent->right.get()) {
            parent->right = nullptr;
            parent->rightVal = 0;
        }

        changed = true;
    }

    if (!changed && this->left) {
        changed = this->left->explode(depth + 1);
    }
    if (!changed && this->right) {
        changed = this->right->explode(depth + 1);
    }

    return changed;
}

bool TreeNode::split() {
    bool changed = false;

    if (!this->left && this->leftVal >= 10) {
        std::shared_ptr<TreeNode> new_tree = std::make_shared<TreeNode>();
        new_tree->parent = shared_from_this();

        new_tree->leftVal = this->leftVal / 2;
        new_tree->rightVal = (this->leftVal + 1) / 2;

        this->left = new_tree;
        changed = true;
    } else if (this->left) {
        changed = this->left->split();
    }


    if (!changed && !this->right && this->rightVal >= 10) {
        std::shared_ptr<TreeNode> new_tree = std::make_shared<TreeNode>();
        new_tree->parent = shared_from_this();

        new_tree->leftVal = this->rightVal / 2;
        new_tree->rightVal = (this->rightVal + 1) / 2;

        this->right = new_tree;
        changed = true;
    } else if (!changed && this->right) {
        changed = this->right->split();
    }

    return changed;
}

std::shared_ptr<TreeNode> TreeNode::parseInput(const std::string& input) {
    int idx = 0;
    return parseInput(input, idx, {});
}

int TreeNode::magnitude() const {
    int sum = 0;

    if (!left) {
        sum += 3 * leftVal;
    } else {
        sum += 3 * left->magnitude();
    }

    if (!right) {
        sum += 2 * rightVal;
    } else {
        sum += 2 * right->magnitude();
    }

    return sum;
}

std::shared_ptr<TreeNode> TreeNode::copy(std::shared_ptr<TreeNode> par) const {
    std::shared_ptr<TreeNode> ptr = std::make_shared<TreeNode>();
    ptr->parent = std::move(par);

    if (left) {
        ptr->left = left->copy(ptr);
    } else {
        ptr->leftVal = leftVal;
    }

    if (right) {
        ptr->right = right->copy(ptr);
    } else {
        ptr->rightVal = rightVal;
    }


    return ptr;
}

TreeNode::TreeNode() = default;

std::shared_ptr<TreeNode> operator+(const std::shared_ptr<TreeNode>& lhs, const std::shared_ptr<TreeNode>& rhs) {
    std::shared_ptr<TreeNode> res = std::make_shared<TreeNode>();
    auto left = lhs->copy(res);
    auto right = rhs->copy(res);
    res->left = left;
    res->right = right;

    res->reduce();

    return res;
}
