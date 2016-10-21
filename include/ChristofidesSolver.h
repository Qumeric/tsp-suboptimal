#ifndef TSP_SUBOPTIMAL_CHRISTOFIDES_H
#define TSP_SUBOPTIMAL_CHRISTOFIDES_H

#include <set>
#include "constants.h"
#include "Edge.h"

class ChristofidesSolver : public ISolver {
private:
    std::set<size_t> findOddDegree(const vector<vector<size_t>> &adjList);

public:
    using ISolver::ISolver;

    double solve(size_t initial_vertex = 0) override;

    std::set<Edge> findGreedyPerfectMatching(std::set<size_t> vertices);

    std::set<Edge> findMinimumPerfectMatching(std::set<size_t> vertices);
};

#endif // TSP_SUBOPTIMAL_CHRISTOFIDES_H
