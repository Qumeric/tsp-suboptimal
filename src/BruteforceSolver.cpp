#include <vector>
#include <algorithm>
#include <ISolver.h>
#include <BruteforceSolver.h>

double BruteforceSolver::solve_rec(vector<bool> &used, size_t current_vertex, size_t initial_vertex, double len,
                                   size_t num) {
    size_t n = g.getSize();
    if (num == n || len >= answer) {
        if (len <= answer) {
            answer = len;
            best_path = path;
        }
        return len;
    }
    used[current_vertex] = true;
    path.push_back(current_vertex);
    for (size_t i = 0; i < n; i++) {
        if (!used[i] || (i == initial_vertex && num == n - 1)) {
            solve_rec(used, i, initial_vertex, len + g.getDistance(current_vertex, i), num + 1);
        }
    }
    used[current_vertex] = false;
    path.pop_back();
    return answer;
}

double BruteforceSolver::solve(size_t initial_vertex) {
    vector<bool> used(g.getSize());
    return solve_rec(used, initial_vertex, initial_vertex);
}
