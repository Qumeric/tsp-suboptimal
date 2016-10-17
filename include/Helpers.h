#ifndef TSP_SUBOPTIMAL_HELPERS_H
#define TSP_SUBOPTIMAL_HELPERS_H

#include "Graph.h"

class Helpers {
public:
    static double get_random(double max_cord, double min_cord = 0);

    static vector<size_t> get_euler_cycle(const vector<vector<size_t>> &tree, size_t v);

    static double calc_length(const Graph &g, const vector<size_t> &cycle);

private:
    static void get_euler_cycle_rec(const vector<vector<size_t>> &tree, size_t v, vector<size_t> &answer);
};

#endif // TSP_SUBOPTIMAL_HELPERS_H
