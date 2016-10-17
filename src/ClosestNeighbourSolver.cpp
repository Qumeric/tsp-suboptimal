#include <vector>
#include <algorithm>
#include <Graph.h>
#include <ClosestNeighbourSolver.h>

double
ClosestNeighbourSolver::solve_rec(vector<bool> &used, size_t current_vertex, size_t initial_vertex,
                                  double len) {
    best_path.push_back(current_vertex);
    size_t n = g.getSize();
    size_t i = 0;
    // Find first unused vertex
    while (used[i]) ++i;
    // If all vertices are used, close cycle
    if (i >= n) {
        return len + g.getDistance(current_vertex, initial_vertex);
    }
    size_t closestNeighbour = i;
    while (++i < n) {
        if (!used[i] && g.getDistance(current_vertex, i) < g.getDistance(current_vertex, closestNeighbour))
            closestNeighbour = i;
    }
    used[closestNeighbour] = true;
    return solve_rec(used, closestNeighbour, initial_vertex, len + g.getDistance(current_vertex, closestNeighbour));
}

double ClosestNeighbourSolver::solve(size_t initial_vertex) {
    vector<bool> used(g.getSize());
    used[initial_vertex] = true;
    return answer = solve_rec(used, initial_vertex, initial_vertex, 0);
}
