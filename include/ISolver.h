#ifndef TSP_SUBOPTIMAL_ISOLVER_H
#define TSP_SUBOPTIMAL_ISOLVER_H


#include <cstddef>
#include "Graph.h"
#include "constants.h"

class ISolver {
protected:
    double answer = INF;
    const Graph &g;
    vector<size_t> path;
    vector<size_t> best_path;
public:
    virtual ~ISolver() {}

    ISolver() = delete;

    ISolver(const Graph &g) : g(g) {}

    /**
     * Solve Travelling Salesman Problem.
     * @param initial_vertex first vertex in this path.
     * @return length of shortest found hamiltonian cycle.
     */
    virtual double solve(size_t initial_vertex = 0) = 0;

    /**
     * Get FIXME
     * @return
     */
    virtual vector<size_t> getPath() {
        if (best_path.empty())
            solve();
        return best_path;
    };

    virtual double getAnswer() {
        if (answer == INF)
            solve();
        return answer;
    }
};


#endif //TSP_SUBOPTIMAL_ISOLVER_H
