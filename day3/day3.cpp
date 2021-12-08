#include "day3.h"
#include "common.h"

#include <algorithm>

int day3_part1(const std::vector<std::string>& input) {
    auto str_len = input[0].length();
    std::vector<int> one_freq(str_len, 0);

    for (const auto& string : input) {
        for (int i = 0; i < one_freq.size(); ++i) {
            if (string[i] == '1') {
                ++one_freq[i];
            }
        }
    }

    int gamma = 0;
    int epsilon = 0;
    int size = static_cast<int>(input.size());

    for (int i = 0; i < str_len; ++i) {
        int shift_amount = static_cast<int>(str_len) - i - 1;
        if (one_freq[i] > size / 2) {
            gamma += 1 << shift_amount;
        } else {
            epsilon += 1 << shift_amount;
        }
    }

    return gamma * epsilon;
}

int one_freq_at(const std::vector<std::string>& list, int index) {
    int freq = 0;
    for (const auto& string : list) {
        if (string[index] == '1') {
            freq += 1;
        }
    }

    return freq;
}

int day3_part2(const std::vector<std::string>& input) {
    auto str_len = input[0].length();
    std::vector<std::string> cur_ox = input;
    int i = 0;

    while (i < str_len && cur_ox.size() > 1) {
        int one_freq = one_freq_at(cur_ox, i);
        char most_common = '0';
        std::vector<std::string> new_ox;

        if (one_freq >= cur_ox.size() - one_freq) {
            most_common = '1';
        }

        for (const auto& string : cur_ox) {
            if (string[i] == most_common) {
                new_ox.push_back(string);
            }
        }

        cur_ox = new_ox;
        ++i;
    }

    i = 0;
    std::vector<std::string> cur_co2 = input;
    while (i < str_len && cur_co2.size() > 1) {
        int one_freq = one_freq_at(cur_co2, i);
        char most_common = '0';
        std::vector<std::string> new_co2;

        if (one_freq >= cur_co2.size() - one_freq) {
            most_common = '1';
        }

        for (const auto& string : cur_co2) {
            if (string[i] != most_common) {
                new_co2.push_back(string);
            }
        }

        cur_co2 = new_co2;
        ++i;
    }

    return stringToBinary(cur_ox[0]) * stringToBinary(cur_co2[0]);
}
