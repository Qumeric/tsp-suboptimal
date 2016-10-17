#ifndef TSP_SUBOPTIMAL_MST_H
#define TSP_SUBOPTIMAL_MST_H

#include "constants.h"
#include "Graph.h"

class MST {
private:
    double length;
    vector<vector<size_t>> mst; // Adjacency list
public:
    MST(const Graph &g, size_t initial_vertex = 0, const vector<size_t> &banned = vector<size_t>());

    double getLength() const;

    vector<vector<size_t>> toAdjList() const;
};

#endif // TSP_SUBOPTIMAL_MST_H
