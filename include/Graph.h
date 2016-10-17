#ifndef TSP_SUBOPTIMAL_GRAPH_H
#define TSP_SUBOPTIMAL_GRAPH_H


#include <cstddef>
#include <vector>
#include "Point.h"
#include "Helpers.h"

using std::vector;

class Graph {
private:
    vector<vector<double>> adjMatrix;

    Graph() {}

    static vector<Point> generateRandomPoints(size_t count);

public:
    Graph(size_t size);

    Graph(vector<Point> points);

    void setDistance(size_t u, size_t v, double distance);

    size_t getSize() const;

    double getDistance(size_t u, size_t v) const;

    void resize(size_t size);
};


#endif //TSP_SUBOPTIMAL_GRAPH_H
