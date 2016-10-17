#ifndef TSP_SUBOPTIMAL_TWOOPTIMAL_H
#define TSP_SUBOPTIMAL_TWOOPTIMAL_H

#include "constants.h"
#include "Graph.h"
#include "ISolver.h"
#include "MST.h"

class TwoOptimalSolver : public ISolver {
public:
    using ISolver::ISolver;

    double solve(size_t initial_vertex);
};

#endif // TSP_SUBOPTIMAL_TWOOPTIMAL_H
