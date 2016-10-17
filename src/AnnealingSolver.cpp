#include <vector>
#include <algorithm>
#include <iostream>
#include <AnnealingSolver.h>
#include <functional>
#include <Helpers.h>


double AnnealingSolver::prob(double old, double nw, double t) {
    return Helpers::get_random(1) < exp((old - nw) / t);
}

vector<size_t> AnnealingSolver::mutate(vector<size_t> cycle) {
    size_t l = rand() % cycle.size();
    size_t r = rand() % cycle.size() + 1;
    if (r < l) std::swap(l, r);
    reverse(cycle.begin() + l, cycle.begin() + r); // Note that cycle is passed by value
    return cycle;
}

vector<size_t> AnnealingSolver::gen_random_cycle() const {
    size_t n = g.getSize();
    vector<size_t> cycle(n + 1);
    std::iota(cycle.begin() + 1, cycle.end() - 1, 1);
    std::random_shuffle(cycle.begin() + 1, cycle.end() - 1);
    return cycle;
}

double AnnealingSolver::solve(size_t initial_vertex) {  // initial_vertex do not affect anything
    double temp = MAX_TEMP; // Temperature
    path = gen_random_cycle();
    double d = Helpers::calc_length(g, path);
    for (size_t i = 1; temp > 1; i++) {
        temp = MAX_TEMP / i; // Linear (may be bad) FIXME implement other strategies
        vector<size_t> candidate = mutate(path);
        double newd = Helpers::calc_length(g, candidate);
        if (newd <= d || prob(d, newd, temp)) {
            path = candidate;
            d = newd;
        }
    }
    best_path = vector<size_t>(path.begin(), path.end() - 1);
    return answer = d;
}
