#include <Graph.h>
#include <Helpers.h>

vector<Point> Graph::generateRandomPoints(size_t count) {
    const size_t MAX_CORD = 1000;
    vector<Point> points(count);
    for (size_t i = 0; i < count; i++) {
        Point point = {Helpers::get_random(MAX_CORD), Helpers::get_random(MAX_CORD)};
        points[i] = point;
    }
    return points;
}

Graph::Graph(size_t size) : Graph(generateRandomPoints(size)) {}

Graph::Graph(vector<Point> points) {
    this->resize(points.size());
    for (size_t i = 0; i < getSize(); i++) {
        for (size_t j = i + 1; j < getSize(); j++) {
            setDistance(i, j, Point::distance(points[i], points[j]));
        }
    }
}

void Graph::resize(size_t size) {
    adjMatrix.resize(size);
    for (auto &row: adjMatrix) {
        row.resize(size);
    }
}

void Graph::setDistance(size_t u, size_t v, double distance) {
    adjMatrix[u][v] = adjMatrix[v][u] = distance;
}

size_t Graph::getSize() const {
    return adjMatrix.size();
}

double Graph::getDistance(size_t u, size_t v) const {
    return adjMatrix[u][v];
}
