#ifndef TSP_SUBOPTIMAL_ISOLVER_H
#define TSP_SUBOPTIMAL_ISOLVER_H


#include <cstddef>
#include "Graph.h"

class ISolver {
public:
    virtual ~ISolver() {}

    virtual double solve(const Graph &, size_t initial_vertex = 0) = 0;
};


#endif //TSP_SUBOPTIMAL_ISOLVER_H
