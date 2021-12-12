#include "day12.h"
#include <numeric>
#include <queue>
#include <utility>
#include <iostream>

int num_paths(const std::shared_ptr<GraphNode>& start, std::unordered_set<std::string> path_map) {
    if (start->name == "end") {
        return 1;
    }
    if (start->small) {
        path_map.insert(start->name);
    }

    int paths = 0;

    for (const auto& neighbour : start->connected) {
        if (path_map.count(neighbour->name) && neighbour->small) {
            continue;
        }

        paths += num_paths(neighbour, path_map);
    }

    return paths;
}

int num_paths_2(const std::shared_ptr<GraphNode>& start, std::unordered_set<std::string> path_map,
                const std::string& twice, bool initialized, std::unordered_set<std::string>& path_set,
                std::string str) {
    if (start->name == "end") {
        path_set.insert(str);
        return 1;
    }

    if (start->small) {
        path_map.insert(start->name);
    }

    int paths = 0;

    for (const auto& neighbour : start->connected) {
        if (!path_map.count(neighbour->name) && neighbour->small &&
            neighbour->name != "start" && neighbour->name != "end") {
            if (!initialized) {
                paths += num_paths_2(neighbour, path_map, neighbour->name, true, path_set,
                                     str + " " + neighbour->name);
            }
        }

        if (neighbour->small && path_map.count(neighbour->name)) {
            if (initialized && neighbour->name == twice) {
                paths += num_paths_2(neighbour, path_map, "", true,
                                     path_set, str + " " + neighbour->name);
            }
            continue;
        }

        paths += num_paths_2(neighbour, path_map, twice, initialized,
                             path_set, str + " " + neighbour->name);
    }

    return paths;
}

std::shared_ptr<GraphNode> get_input(const std::vector<std::string>& input) {
    std::unordered_map<std::string, std::shared_ptr<GraphNode>> node_map;
    std::shared_ptr<GraphNode> start;

    for (const auto& line : input) {
        auto nodes = splitString(line, "-");

        if (!node_map.count(nodes[0])) {
            node_map[nodes[0]] = std::make_shared<GraphNode>(nodes[0]);
        }
        if (!node_map.count(nodes[1])) {
            node_map[nodes[1]] = std::make_shared<GraphNode>(nodes[1]);
        }

        const auto& node_0 = node_map[nodes[0]];
        const auto& node_1 = node_map[nodes[1]];
        node_0->addNeighbour(node_1);
        node_1->addNeighbour(node_0);

        if (node_0->name == "start") {
            start = node_0;
        }
        if (node_1->name == "start") {
            start = node_1;
        }
    }

    return start;
}

int day12_part1(const std::vector<std::string>& input) {
    auto node = get_input(input);
    return num_paths(node, {});
}

int day12_part2(const std::vector<std::string>& input) {
    auto node = get_input(input);
    std::unordered_set<std::string> set;
    num_paths_2(node, {}, "", false, set, "start");
    return set.size();
}

GraphNode::GraphNode(std::string name) : name(std::move(name)) {
    if (std::all_of(this->name.begin(), this->name.end(), [](const char c) { return std::islower(c); })) {
        small = true;
    } else {
        small = false;
    }
}

void GraphNode::addNeighbour(const std::shared_ptr<GraphNode>& node) {
    connected.push_back(node);
}
