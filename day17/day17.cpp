
#include "day17.h"

#include <utility>
#include <queue>
#include <numeric>

std::pair<double, double> solve_quadratic(double a, double b, double c) {
    return std::make_pair<double, double>((-b + std::sqrt(b * b - 4 * a * c)) / (2 * a),
                                          (-b - std::sqrt(b * b - 4 * a * c)) / (2 * a));
}

bool check_overshoot(std::int64_t y_min, std::int64_t y_max, std::int64_t v) {
    for (auto y = y_min; y <= y_max; ++y) {
        auto t = solve_quadratic(-0.5, v + 0.5, -y);
        double intpart;
        if (t.first >= 0 && std::modf(t.first, &intpart) == 0.0) {
            return true;
        }

        if (t.second >= 0 && std::modf(t.second, &intpart) == 0.0) {
            return true;
        }
    }

    return false;
}


std::int64_t day17_part1(const std::vector<std::string>& input) {
    auto range = Input::get(input[0]);

    auto y_min = range.lowerLeft.y;
    auto y_max = range.upperRight.y;

    std::int64_t velocity_min = range.lowerLeft.y;
    std::int64_t velocity_max = 1e5;



    for (; velocity_max >= velocity_min; --velocity_max) {
        if (check_overshoot(y_min, y_max, velocity_max)) {
            break;
        }
    }

    double value = 0;
    int t = 0;
    std::vector<double> values;

    while (value > y_min) {
       value = velocity_max * t - (t * (t - 1)) / 2.0;
       t += 1;
       values.push_back(value);
    }

    return static_cast<std::int64_t>(*std::max_element(values.begin(), values.end()));
}

std::int64_t day17_part2(const std::vector<std::string>& input) {
    auto range = Input::get(input[0]);

    auto x_min = range.lowerLeft.x;
    auto x_max = range.upperRight.x;

    auto y_min = range.lowerLeft.y;
    auto y_max = range.upperRight.y;

    int num_vals = 0;

    for (double v_x = 0; v_x <= x_max; v_x += 1.0) {
        for (double v_y = -500; v_y <= 500; v_y += 1.0) {
            double v_xx = v_x;
            double v_yy = v_y;
            double pos_x = 0;
            double pos_y = 0;
            for (double t = 0; t < 5000; ++t) {

                if (pos_x >= x_min && pos_x <= x_max && pos_y >= y_min && pos_y <= y_max) {
                    ++num_vals;
                    break;
                }

                pos_x += v_xx;
                v_xx = std::max(v_xx - 1.0, 0.0);
                pos_y += v_yy;
                v_yy = v_yy - 1;
            }
        }
    }


    return num_vals;
}

Input::Input(Point2l lower_left, Point2l upper_right) : lowerLeft(lower_left), upperRight(upper_right)
{
}

Input Input::get(const std::string& input) {
    // target area: x=20..30, y=-10..-5
    auto text_coords = splitString(input, ": ")[1];
    auto ranges = splitString(text_coords, ", ");

    auto x_range = splitString(splitString(ranges[0], "=")[1], "..");
    auto y_range = splitString(splitString(ranges[1], "=")[1], "..");

    Point2l lower_left{std::stoi(x_range[0]), std::stoi(y_range[0])};
    Point2l upper_right{std::stoi(x_range[1]), std::stoi(y_range[1])};

    return {lower_left, upper_right};
}
