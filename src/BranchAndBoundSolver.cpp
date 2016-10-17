#include <vector>
#include <MST.h>
#include <BranchAndBoundSolver.h>
#include <numeric>
#include <algorithm>

double BranchAndBoundSolver::solve_(size_t current_vertex, double weight, size_t initial_vertex) {
    size_t n = g.getSize();
    used[current_vertex] = true;
    path.push_back(current_vertex);
    bool found = false;
    double mst_len = 0;
    if (current_vertex == initial_vertex) {
        ans = MST(g).getLength() * 2; // 2-optimal solution with MST
    }

    size_t mst_init;
    bool mst_initialized = false;

    // FIXME one vertex problem (sometimes can't find the most optimal solution...)
    double shortestA = INF, shortestB = INF;
    for (size_t i = 0; i < n; i++) {
        if (used[i]) continue;
        if (g.getDistance(initial_vertex, i) < shortestA) {
            shortestA = g.getDistance(initial_vertex, i);
            mst_init = i;
            mst_initialized = true;
        }
        shortestB = std::min(shortestB, g.getDistance(current_vertex, i));
    }

    if (mst_initialized) {
        mst_len = MST(g, mst_init, path).getLength();
    }

    vector<size_t> seq(n);
    std::iota(seq.begin(), seq.end(), 0);
    std::random_shuffle(seq.begin(), seq.end());


    for (size_t i: seq) { // randomized for better performance
        if (!used[i]) {
            found = true;
            if (weight + shortestA + shortestB + mst_len < ans) {
                solve_(i, weight + g.getDistance(current_vertex, i), initial_vertex);
            }
        }
    }
    if (!found) { // All vertices already used, need to close the cycle
        if (weight + g.getDistance(current_vertex, initial_vertex) < ans) {
            ans = weight + g.getDistance(current_vertex, initial_vertex);
            best_path = path;
        }
    }
    path.pop_back();
    used[current_vertex] = false;
    return ans;
}

double BranchAndBoundSolver::solve(size_t initial_vertex) {
    used.resize(g.getSize());
    std::fill(used.begin(), used.end(), 0);
    return answer = solve_(initial_vertex, 0, initial_vertex);
}

