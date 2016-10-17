#include <vector>
#include <algorithm>
#include <iostream>
#include "ant.h"

using namespace std;

// IDEA: local search imporving (2-okr?)
double phero[MAX_SIZE][MAX_SIZE];
// FIXME const
size_t ITER_COUNT = 100;
double ALPHA = 1.5; // zero for greedy
double BETA  = 9; // zero for crazy
double Q = 8500;
double FORGET = 0.4;
double MAX_PHEROMONE_INIT = 2;
double ELITE = 0.2; // kind of pseudo

double rec_ant(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v, vector<bool> &used, vector<size_t>& path, size_t beg, double dist = 0, size_t cnt=1) {
    path.push_back(v);
    if (cnt == n) {
        path.push_back(beg);
        return dist + graph[beg][v];
    }
    used[v] = true;
    vector<double> prob(n);
    for (size_t i = 0; i < n; i++) {
        if (i != 0)
            prob[i] += prob[i-1];
        if (!used[i]) {
            prob[i] += pow(1.0/graph[v][i], BETA) * pow(phero[v][i], ALPHA);
        }
    }

    double var = get_random(prob[n-1]);

    // Always returns
    for (size_t i = 0; i < n; i++) {
        if (var < prob[i]) {
            return rec_ant(graph, n, i, used, path, beg, dist + graph[v][i], cnt+1);
        }
    }
}


double solve_ant(double graph[MAX_SIZE][MAX_SIZE], size_t n) {
    double ans = 1e9;
    vector<bool> used(n);
    vector<size_t> path;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            phero[i][j] = get_random(1, MAX_PHEROMONE_INIT);
        }
    }
    size_t v;
    for (size_t iter = 0; iter < ITER_COUNT; iter++) {
        v = rand()%n;
        double len = rec_ant(graph, n, v, used, path, v);
        ans = min(ans, len);
        phero[path[0]][path[n]] *= (1-FORGET);
        phero[path[0]][path[n]] += Q/len;
        for (size_t i = 0; i < n; i++) {
            phero[path[i]][path[i+1]] *= (1-FORGET);
            phero[path[i]][path[i+1]] += Q/len;
        }
        path.clear();
        fill(used.begin(), used.end(), false);
    }
    return ans;
}
