#ifndef AOC_COMMON_H
#define AOC_COMMON_H

#include <vector>
#include <string>
#include <istream>

std::vector<std::string> readInputLines(std::istream& i);

std::vector<std::string> splitString(const std::string& string, const std::string& delimiter);

int stringToBinary(const std::string& s);

template<typename T>
struct Point2D {
    T x;
    T y;

    Point2D(T x, T y) : x(x), y(y) {}

    bool operator==(const Point2D& rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const Point2D& rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Point2D& other) const {
        if (x < other.x) { return true; }
        if (x > other.x) { return false; }
        if (y < other.y) { return true; }
        return false;
    }
};

namespace std {
    template<typename T>
    struct hash<Point2D<T>>
    {
        std::size_t operator()(const Point2D<T>& k) const
        {
            using std::hash;

            return hash<T>()(k.x)
                   ^ (hash<T>()(k.y) << 1);
        }
    };
}

template<typename T>
struct LineSegment {
    Point2D<T> begin;
    Point2D<T> end;

    LineSegment(Point2D<T> t1, Point2D<T> t2) : begin(t1), end(t2) {}
};

using Point2i = Point2D<int>;
using Line2i = LineSegment<int>;

using Point2l = Point2D<std::int64_t>;


std::vector<Point2i> get_neighbours_8(int row, int col, std::size_t height, std::size_t width);

#endif //AOC_COMMON_H
