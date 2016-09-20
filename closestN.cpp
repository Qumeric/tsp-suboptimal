#include <vector>
#include <algorithm>
#include <iostream>
#include "closestN.h"

using namespace std;

double solve_cn_rec(double graph[MAX_SIZE][MAX_SIZE], vector<bool>& used, size_t n, size_t v, double len) {
    size_t i = 0;
    while(used[i]) ++i;
    if (i >= n)
        return len + graph[v][INITIAL_VERTEX];
    size_t closest = i;
    while(++i < n) {
        if (!used[i] && graph[v][i] < graph[v][closest])
            closest = i;
    }
    used[closest] = true;
    return solve_cn_rec(graph, used, n, closest, len + graph[v][closest]);
}

double solve_cn(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v, double len) {
    vector<bool> used(n);
    double answer = solve_cn_rec(graph, used, n, v, len);
    return answer;
}
