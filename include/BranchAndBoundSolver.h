#ifndef TSP_SUBOPTIMAL_BRANCHANDBOUND_H
#define TSP_SUBOPTIMAL_BRANCHANDBOUND_H

#include "ISolver.h"
#include "constants.h"

#include <MST.h>

class BranchAndBoundSolver : public ISolver {
private:
    vector<bool> used;
    vector<size_t> path;
    double ans = INF; // FIXME use first approx
    vector<size_t> best_path;

    double solve_(const Graph& g, size_t current_vertex = 0, double weight = 0, size_t initial_vertex = 0);
public:
    double solve(const Graph&, size_t initial_vertex = 0);
};
#endif // TSP_SUBOPTIMAL_BRANCHANDBOUND_H
