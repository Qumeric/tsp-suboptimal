#ifndef TSP_SUBOPTIMAL_BRUTEFORCE_H
#define TSP_SUBOPTIMAL_BRUTEFORCE_H

#include "constants.h"

class BruteforceSolver : public ISolver {
private:
    double solve_brute_rec(Graph g, vector<bool> &used, double &answer,
                           size_t current_vertex, size_t initial_vertex, double len = 0, size_t num = 0);

public:
    double solve(const Graph &g, size_t initial_vertex = 0) override;
};

#endif // TSP_SUBOPTIMAL_BRUTEFORCE_H
