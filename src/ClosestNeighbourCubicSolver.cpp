#include <vector>
#include <algorithm>
#include <Graph.h>
#include <ClosestNeighbourCubicSolver.h>

double ClosestNeighbourCubicSolver::solve_rec(vector<bool> &used, size_t current_vertex, size_t initial_vertex,
                                              double len) {
    size_t n = g.getSize();
    size_t i = 0;
    // Find first unused vertex
    while (used[i]) ++i;
    // If all vertices are used, close cycle
    if (i >= n) {
        return len + g.getDistance(current_vertex, initial_vertex);
    }

    // Try to add vertex to the end of the path
    size_t closestNeighbour = i;
    for (size_t v = i; v < n; v++) {
        if (!used[v] && g.getDistance(current_vertex, v) < g.getDistance(current_vertex, closestNeighbour))
            closestNeighbour = v;
    }



    // try to add vertex to some position on the path
    bool foundShorter = false;
    double shortestDistance = g.getDistance(current_vertex, closestNeighbour);
    size_t vertexToAdd;
    vector<size_t>::iterator addAfter;

    if (best_path.size() == 1) { // there are no edges in path
        goto addToTheEnd;
    }

    for (auto it = best_path.begin(); it != best_path.end() - 1; it++) {
        for (size_t v = i; v < n; v++) {
            if (used[v])
                continue;
            // Insert a vertex between two in path
            double newDistance = g.getDistance(*it, v) + g.getDistance(v, *(it + 1)) - g.getDistance(*it, *(it + 1));
            if (newDistance < shortestDistance) {
                shortestDistance = newDistance;
                foundShorter = true;
                vertexToAdd = v;
                addAfter = it;
            }
        }
    }

    if (foundShorter) {
        used[vertexToAdd] = true;
        best_path.insert(addAfter + 1, vertexToAdd);
        return solve_rec(used, current_vertex, initial_vertex, len + shortestDistance);
    }

    addToTheEnd:
    used[closestNeighbour] = true;
    best_path.push_back(closestNeighbour);
    return solve_rec(used, closestNeighbour, initial_vertex, len + g.getDistance(current_vertex, closestNeighbour));
}

double ClosestNeighbourCubicSolver::solve(size_t initial_vertex) {
    vector<bool> used(g.getSize());
    used[initial_vertex] = true;
    best_path.push_back(initial_vertex);
    return answer = solve_rec(used, initial_vertex, initial_vertex, 0);
}
