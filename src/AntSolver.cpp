#include <vector>
#include <algorithm>
#include <Graph.h>
#include "AntSolver.h"

using namespace std;

double AntSolver::rec_ant(const Graph &g, size_t current_vertex, vector<bool> &used, vector<size_t> &path, size_t beg,
                          double dist, size_t cnt) {
    size_t n = g.getSize();
    path.push_back(current_vertex);
    if (cnt == n) {
        path.push_back(beg);
        return dist + g.getDistance(beg, current_vertex);
    }
    used[current_vertex] = true;
    vector<double> prob(n);
    for (size_t i = 0; i < n; i++) {
        if (i != 0)
            prob[i] += prob[i - 1];
        if (!used[i]) {
            prob[i] += pow(1.0 / g.getDistance(current_vertex, i), BETA) * pow(phero[current_vertex][i], ALPHA);
        }
    }

    double var = Helpers::get_random(prob[n - 1]);

    // Always returns
    for (size_t i = 0; i < n; i++) {
        if (var < prob[i]) {
            return rec_ant(g, i, used, path, beg, dist + g.getDistance(current_vertex, i), cnt + 1);
        }
    }
}


double AntSolver::solve(const Graph &g, size_t initial_vertex) { // Initial vertex do not affect anything
    double ans = INF;
    size_t n = g.getSize();
    vector<bool> used(n);
    vector<size_t> path;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            phero[i][j] = Helpers::get_random(1, MAX_PHEROMONE_INIT);
        }
    }
    size_t v;
    for (size_t iter = 0; iter < ITER_COUNT; iter++) {
        v = rand() % n;
        double len = rec_ant(g, v, used, path, v);
        ans = min(ans, len);
        phero[path[0]][path[n]] *= (1 - FORGET);
        phero[path[0]][path[n]] += Q / len;
        for (size_t i = 0; i < n; i++) {
            phero[path[i]][path[i + 1]] *= (1 - FORGET);
            phero[path[i]][path[i + 1]] += Q / len;
        }
        path.clear();
        fill(used.begin(), used.end(), false);
    }
    return ans;
}
