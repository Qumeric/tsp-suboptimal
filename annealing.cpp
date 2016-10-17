#include <vector>
#include <algorithm>
#include <iostream>
#include "annealing.h"

using namespace std;

double calc_length(double graph[MAX_SIZE][MAX_SIZE], vector<size_t>& cycle) {
    double ans = graph[cycle.back()][cycle.front()];
    for (size_t i = 0; i < cycle.size()-1; i++) {
        ans += graph[cycle[i]][cycle[i+1]];
    }
    return ans;
}

double prob(double old, double nw, double t) {
     return get_random(1) < exp((old-nw)/t);
}

vector<size_t> mutate(vector<size_t> cycle) {
    size_t l = rand()%cycle.size();
    size_t r = rand()%cycle.size()+1;
    if (r < l) swap(l, r);
    vector<size_t> ans = cycle;
    reverse(ans.begin()+l, ans.begin()+r);
    return ans;
}

// FIXME useless
vector<size_t> gen_random_cycle(double graph[MAX_SIZE][MAX_SIZE], size_t n) {
    vector<size_t> a(n+1);
    a[n] = 0;
    for (size_t i = 0; i < n; i++)
        a[i] = i;
    return a;
}

const double MAX_T = 100000;
double solve_annealing(double graph[MAX_SIZE][MAX_SIZE], size_t n) {
    double t = MAX_T;
    size_t i = 1;
    vector<size_t> cycle = gen_random_cycle(graph, n);
    double d = calc_length(graph, cycle);
    while(t > 1) {
        t = MAX_T / i; // linear (may be bad)
        vector<size_t> candidate = mutate(cycle);
        double newd = calc_length(graph, candidate);
        if (newd <= d || prob(d, newd, t)) {
            cycle = candidate;
            d = newd;
        }
        ++i;
    }
    return d;
}
