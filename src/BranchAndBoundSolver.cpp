#include <vector>
#include <MST.h>
#include <BranchAndBoundSolver.h>

double BranchAndBoundSolver::solve_(const Graph& g, size_t current_vertex, double weight, size_t initial_vertex) {
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

    // FIXME one vertex problem
    double shortestA = INF, shortestB = INF;
    for (size_t i = 0; i < n; i++) {
        if (used[i]) continue;
        if (g.getDistance(initial_vertex, i) < shortestA) {
            shortestA = g.getDistance(initial_vertex, i);
            mst_init = i;
            mst_initialized = true;
        }
        shortestB = min(shortestB, g.getDistance(current_vertex, i));
    }

    if (mst_initialized) {
        mst_len = MST(g, mst_init, path).getLength();
    }

    for (size_t i = 0; i < n; i++) { // FIXME randomized/sorted
        if (!used[i]) {
            found = true;
            if (weight + shortestA + shortestB + mst_len < ans) {
                solve_(g, i, weight + g.getDistance(current_vertex, i), initial_vertex);
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

double BranchAndBoundSolver::solve(const Graph& g, size_t initial_vertex ) {
    used.resize(g.getSize());
    std::fill(used.begin(), used.end(), 0);
    return solve_(g, initial_vertex, 0, initial_vertex);
}
