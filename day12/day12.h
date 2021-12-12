#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>

#include "common.h"

struct GraphNode {
    std::string name;
    std::vector<std::shared_ptr<GraphNode>> connected;
    bool small;

    GraphNode(std::string  name);

    void addNeighbour(const std::shared_ptr<GraphNode>& node);
};

std::shared_ptr<GraphNode> get_input(const std::vector<std::string>& input);

int num_paths(const std::shared_ptr<GraphNode>& start, std::unordered_set<std::string> path_map);

int num_paths_2(const std::shared_ptr<GraphNode>& start, std::unordered_set<std::string> path_map,
                const std::string& twice, bool initialized, std::unordered_set<std::string>& paths,
                std::string str);

int day12_part1(const std::vector<std::string>& input);

int day12_part2(const std::vector<std::string>& input);

#endif //AOC_DAY2_H
