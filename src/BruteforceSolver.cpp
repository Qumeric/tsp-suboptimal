#include <vector>
#include <algorithm>
#include <ISolver.h>
#include <BruteforceSolver.h>

double BruteforceSolver::solve_brute_rec(Graph g, vector<bool> &used, double &answer,
                                         size_t current_vertex, size_t initial_vertex, double len, size_t num) {
    size_t n = g.getSize();
    if (num == n || len >= answer)
        return len;
    used[current_vertex] = true;
    for (size_t i = 0; i < n; i++) {
        if (!used[i] || (i == initial_vertex && num == n - 1)) {
            answer = min(answer, solve_brute_rec(g, used, answer,
                                                 i, initial_vertex, len + g.getDistance(current_vertex, i), num + 1));
        }
    }
    used[current_vertex] = false;
    return answer;
}

double BruteforceSolver::solve(const Graph &g, size_t initial_vertex) {
    vector<bool> used(g.getSize());
    double answer = INF;
    return solve_brute_rec(g, used, answer, initial_vertex, initial_vertex);
}
