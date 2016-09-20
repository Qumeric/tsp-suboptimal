#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>
inline double get_random(double max_cord, double min_cord = 0) {
    static std::mt19937_64 eng(time(0));
    std::uniform_real_distribution<double> unif(min_cord, max_cord);
    return unif(eng);
}

const double INF = 1e18;
const size_t INITIAL_VERTEX = 0;
const size_t MAX_SIZE = 10000;
const double MAX_CORD = 1000;
#endif
