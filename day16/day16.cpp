
#include "day16.h"

#include <utility>
#include <iostream>
#include <queue>
#include <array>
#include <numeric>

std::unordered_map<char, std::string> HEX_MAP = {
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'A', "1010"},
        {'B', "1011"},
        {'C', "1100"},
        {'D', "1101"},
        {'E', "1110"},
        {'F', "1111"},
};

std::unordered_map<int, PacketType> TYPE_MAP {
        {0, PacketType::SUM},
        {1, PacketType::PRODUCT},
        {2, PacketType::MINIMUM},
        {3, PacketType::MAXIMUM},
        {4, PacketType::LITERAL},
        {5, PacketType::GREATER_THAN},
        {6, PacketType::LESS_THAN},
        {7, PacketType::EQUAL_TO}
};

std::vector<std::shared_ptr<Node>> parseInput(TokenStream& stream, int until, bool use_length) {
    std::vector<std::shared_ptr<Node>> nodes;
    int num_parsed = 0;

    while (!stream.tokens.empty() &&
           (use_length && stream.pos < until) ||
           (!use_length && num_parsed < until)) {
        int version = stream.take(3);
        int type = stream.take(3);

        if (type == 4) {
            std::int64_t num;
            std::vector<std::int64_t> vals;
            do {
                num = stream.take(5);
                vals.push_back((num & ~0x10));
            } while ((num & 0x10) != 0);

            std::int64_t value = 0;
            int shift_amount = (vals.size() - 1) * 4;
            for (std::int64_t val : vals) {
                std::int64_t shifted = val << shift_amount;
                value |= shifted;
                shift_amount -= 4;
            }

            nodes.push_back(std::make_shared<Node>(version, value, PacketType::LITERAL));
        } else {
            int operator_type = stream.take(1);
            if (operator_type == 0) {
                int num_bits = stream.take(15);
                auto children = parseInput(stream, stream.pos + num_bits, true);
                nodes.push_back(std::make_shared<Node>(version, children, TYPE_MAP[type]));
            } else {
                int num_packs = stream.take(11);
                auto children = parseInput(stream, num_packs, false);
                nodes.push_back(std::make_shared<Node>(version, children, TYPE_MAP[type]));
            }
        }

        ++num_parsed;
    }

    return nodes;
}

std::int64_t day16_part1(const std::vector<std::string>& input) {
    TokenStream stream{input[0]};

    auto tree = parseInput(stream, 1, false);
    auto sum = tree[0]->sumVersion();

    return sum;
}

std::int64_t day16_part2(const std::vector<std::string>& input) {
    TokenStream stream{input[0]};

    auto tree = parseInput(stream, 1, false);
    auto sum = tree[0]->getValue();

    return sum;
}

Node::Node(int versionNumber, std::int64_t value, PacketType type)
    : versionNumber(versionNumber), value(value), type(type)
{}

Node::Node(int versionNumber, std::vector<std::shared_ptr<Node>> nodes, PacketType type)
    : versionNumber(versionNumber), nodes(std::move(nodes)), type(type), value(0)
{
}

int Node::sumVersion() {
    int sum = versionNumber;
    for (const auto& child : nodes) {
        sum += child->sumVersion();
    }
    return sum;
}

std::int64_t Node::getValue() {
    switch(type) {
        case PacketType::SUM:
            return std::reduce(nodes.begin(), nodes.end(), 0LL, [](const std::int64_t acc, auto& val) {
                return acc + val->getValue();
            });
        case PacketType::PRODUCT:
            return std::reduce(nodes.begin(), nodes.end(), 1LL, [](const std::int64_t acc, auto& val) {
                return acc * val->getValue();
            });
        case PacketType::MINIMUM:
            return std::reduce(nodes.begin(), nodes.end(), std::numeric_limits<std::int64_t>::max(),
                               [](const std::int64_t acc, auto& val) { return std::min(acc, val->getValue()); });
        case PacketType::MAXIMUM:
            return std::reduce(nodes.begin(), nodes.end(), std::numeric_limits<std::int64_t>::min(),
                               [](const std::int64_t acc, auto& val) { return std::max(acc, val->getValue()); });
        case PacketType::LITERAL:
            return value;
        case PacketType::GREATER_THAN:
            return nodes[0]->getValue() > nodes[1]->getValue();
        case PacketType::LESS_THAN:
            return nodes[0]->getValue() < nodes[1]->getValue();
        case PacketType::EQUAL_TO:
            return nodes[0]->getValue() == nodes[1]->getValue();
    }
}

TokenStream::TokenStream(const std::string& tokens) : pos(0) {
    for (const char c : tokens) {
        for (const char h : HEX_MAP[c]) {
            this->tokens.push(h);
        }
    }
}

int TokenStream::take(int num_bits) {
    int res = 0;
    std::string temp;
    for (int i = 0; i < num_bits; ++i) {
        temp.push_back(tokens.front());
        if (tokens.empty()) {
            throw std::runtime_error("This should not happen");
        }
        tokens.pop();
    }

    int shift_val = 0;
    for (int i = 0; i < num_bits; ++i) {
        res |= (temp.back() == '1') << shift_val;
        ++shift_val;
        temp.pop_back();
    }

    pos += num_bits;
    return res;
}

