#ifndef TSP_SUBOPTIMAL_CLOSESTNEIGHBOUR_H
#define TSP_SUBOPTIMAL_CLOSESTNEIGHBOUR_H

#include "constants.h"
#include "ISolver.h"

class ClosestNeighbourSolver : public ISolver {
private:
    double solve_rec(vector<bool> &used, size_t current_vertex, size_t initial_vertex, double len = 0);

public:
    using ISolver::ISolver;

    double solve(size_t initial_vertex = 0) override;
};

#endif // TSP_SUBOPTIMAL_CLOSESTNEIGHBOUR_H
