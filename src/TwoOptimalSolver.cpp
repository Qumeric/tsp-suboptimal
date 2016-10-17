#include <vector>
#include <iostream>
#include <TwoOptimalSolver.h>

double TwoOptimalSolver::solve(const Graph &g, size_t initial_vertex) {
    return MST(g, initial_vertex).getLength() * 2;
    /*
    vector <vector<size_t>> mst = MST(g, initial_vertex).toAdjList();
    vector <size_t> euler_cycle = Helpers::get_euler_cycle(mst, initial_vertex);

    double answer = 0;

    vector<bool> used(g.getSize());
    size_t last = initial_vertex;
    for (size_t i = 1; i < euler_cycle.size(); i++) {
        if (!used[euler_cycle[i]]) {
            answer += g.getDistance(last, euler_cycle[i]);
            last = euler_cycle[i];
            used[euler_cycle[i]] = true;
        }
    }

    return answer;
    */
}
