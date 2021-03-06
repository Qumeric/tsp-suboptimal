#ifndef TSP_SUBOPTIMAL_POINT_H
#define TSP_SUBOPTIMAL_POINT_H

#include <string>
#include <cmath>

using std::abs;

struct Point {
    double x;
    double y;

    static double
    distance(const Point &a, const Point &b, const std::string type = "euclid") { // FIXME use enum and switch/case
        if (type == "euclid") {
            return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
        } else if (type == "manhattan") {
            return abs(a.x - b.x) + abs(a.y - b.y);
        } else if (type == "max") {
            return std::max(abs(a.x - b.x), abs(a.y - b.y));
        } else {
            return -1; // Something went wrong
        }
    }
};

#endif // TSP_SUBOPTIMAL_POINT_H
