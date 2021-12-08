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

    res.push_back(string.substr(start));
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
