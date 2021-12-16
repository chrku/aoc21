#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>

#include "common.h"

enum class PacketType {
    SUM,
    PRODUCT,
    MINIMUM,
    MAXIMUM,
    LITERAL,
    GREATER_THAN,
    LESS_THAN,
    EQUAL_TO
};

struct Node {
    int versionNumber;
    PacketType type;
    std::int64_t value;
    std::vector<std::shared_ptr<Node>> nodes;

    explicit Node(int versionNumber, std::int64_t value, PacketType Type);
    explicit Node(int versionNumber, std::vector<std::shared_ptr<Node>> nodes, PacketType type);

    int sumVersion();
    std::int64_t getValue();
};

struct TokenStream {
    std::queue<char> tokens;
    int pos;

    explicit TokenStream(const std::string& tokens);

    int take(int num_bits);
};

std::vector<std::shared_ptr<Node>> parseInput(TokenStream& stream, int until, bool use_length);

std::int64_t day16_part1(const std::vector<std::string>& input);

std::int64_t day16_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
