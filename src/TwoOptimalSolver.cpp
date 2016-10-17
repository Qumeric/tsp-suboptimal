#include <vector>
#include <iostream>
#include <TwoOptimalSolver.h>
#include <Helpers.h>

// FIXME bug. Sometimes can find better answer than bruteforce.
double TwoOptimalSolver::solve(size_t initial_vertex) {
    vector <vector<size_t>> mst = MST(g, initial_vertex).toAdjList();
    vector <size_t> euler_cycle = Helpers::get_euler_cycle(mst, initial_vertex);

    std::cerr << "Length of MST is: " << MST(g, initial_vertex).getLength() << std::endl;

    answer = g.getDistance(euler_cycle.back(), euler_cycle.front());

    vector<bool> used(g.getSize());
    size_t last = initial_vertex;
    for (size_t i = 1; i < euler_cycle.size(); i++) {
        if (!used[euler_cycle[i]]) {
            best_path.push_back(last);
            answer += g.getDistance(last, euler_cycle[i]);
            last = euler_cycle[i];
            used[euler_cycle[i]] = true;
        }
    }

    return answer;
}
