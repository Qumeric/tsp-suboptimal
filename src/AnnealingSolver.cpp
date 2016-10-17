#include <vector>
#include <algorithm>
#include <iostream>
#include <AnnealingSolver.h>
#include <functional>

double AnnealingSolver::calc_length(const Graph &g, vector<size_t> &cycle) {
    double length = g.getDistance(cycle.back(), cycle.front());
    for (size_t i = 0; i < cycle.size() - 1; i++)
        length += g.getDistance(cycle[i], cycle[i + 1]);
    return length;
}

double AnnealingSolver::prob(double old, double nw, double t) {
    return Helpers::get_random(1) < exp((old - nw) / t);
}

vector<size_t> AnnealingSolver::mutate(vector<size_t> cycle) {
    size_t l = rand() % cycle.size();
    size_t r = rand() % cycle.size() + 1;
    if (r < l) swap(l, r);
    reverse(cycle.begin() + l, cycle.begin() + r); // Note that cycle is passed by value
    return cycle;
}

vector<size_t> AnnealingSolver::gen_random_cycle(const Graph &g) {
    size_t n = g.getSize();
    vector<size_t> cycle(n + 1);
    std::iota(cycle.begin() + 1, cycle.end() - 1, 1);
    std::random_shuffle(cycle.begin() + 1, cycle.end() - 1);
    return cycle;
}

double AnnealingSolver::solve(const Graph &g, size_t initial_vertex) {  // initial_vertex do not affect anything
    double temp = MAX_TEMP; // Temperature
    vector<size_t> cycle = gen_random_cycle(g);
    double d = calc_length(g, cycle);
    for (size_t i = 1; temp > 1; i++) {
        temp = MAX_TEMP / i; // Linear (may be bad) FIXME implement other strategies
        vector<size_t> candidate = mutate(cycle);
        double newd = calc_length(g, candidate);
        if (newd <= d || prob(d, newd, temp)) {
            cycle = candidate;
            d = newd;
        }
    }
    return d;
}
