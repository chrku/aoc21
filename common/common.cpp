#include "common.h"

std::vector<std::string> readInputLines(std::istream& i) {
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(i, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::vector<std::string> splitString(const std::string& string, const std::string& delimiter) {
    std::size_t start = 0;
    std::size_t end = 0;
    std::size_t delim_length = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((end = string.find(delimiter, start)) != std::string::npos) {
        token = string.substr(start, end - start);
        start = end + delim_length;
        if (!token.empty()) {
            res.push_back(token);
        }
    }

    auto last_token = string.substr(start);
    if (!last_token.empty()) {
        res.push_back(last_token);
    }
    return res;
}

int stringToBinary(const std::string& s) {
    int res = 0;
    int str_len = static_cast<int>(s.length());

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '1') {
            res += 1 << (str_len - i - 1);
        }
    }

    return res;
}

std::vector<Point2i> get_neighbours_8(int row, int col, std::size_t height, std::size_t width) {
    std::vector<Point2i> neighbours;
    if (row > 0) {
        neighbours.emplace_back(col, row - 1);
    }
    if (col > 0) {
        neighbours.emplace_back(col - 1, row);
    }
    if (row > 0 && col > 0) {
        neighbours.emplace_back(col - 1, row - 1);
    }

    if (row < height - 1) {
        neighbours.emplace_back(col, row + 1);
    }
    if (col < width - 1) {
        neighbours.emplace_back(col + 1, row);
    }
    if (row < height - 1 && col < width - 1) {
        neighbours.emplace_back(col + 1, row + 1);
    }

    if (row > 0 && col < width - 1) {
        neighbours.emplace_back(col + 1, row - 1);
    }
    if (row < height - 1 && col > 0) {
        neighbours.emplace_back(col - 1, row + 1);
    }

    return neighbours;
}
