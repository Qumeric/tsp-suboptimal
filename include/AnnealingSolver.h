#ifndef TSP_SUBOPTIMAL_ANNEALING_H
#define TSP_SUBOPTIMAL_ANNEALING_H

#include "ISolver.h"

class AnnealingSolver : public ISolver {
private:
    static constexpr double MAX_TEMP = 100000.0f;


    static double prob(double old, double nw, double t);

    static vector<size_t> mutate(vector<size_t> cycle);

    vector<size_t> gen_random_cycle() const;

public:
    using ISolver::ISolver;

    double solve(size_t initial_vertex = 0) override;
};

#endif // TSP_SUBOPTIMAL_ANNEALING_H
