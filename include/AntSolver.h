#ifndef TSP_SUBOPTIMAL_ANT_H
#define TSP_SUBOPTIMAL_ANT_H

#include "ISolver.h"
#include "constants.h"

class AntSolver : public ISolver {
private:
    double phero[1000][1000];
    size_t ITER_COUNT = 100;
    double ALPHA = 1.5; // zero for greedy
    double BETA = 9; // zero for crazy
    double Q = 8500;
    double FORGET = 0.4;
    double MAX_PHEROMONE_INIT = 2;
public:
    using ISolver::ISolver;

    double rec_ant(size_t current_vertex, vector<bool> &used, vector<size_t> &path, size_t beg,
                   double dist = 0, size_t cnt = 1);

    double solve(size_t initial_vector) override;
};

#endif // TSP_SUBOPTIMAL_ANT_H
