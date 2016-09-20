#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "bruteforce.h"

using namespace std;

double solve_brute_rec(double graph[MAX_SIZE][MAX_SIZE], vector<bool>& used, double& answer, size_t n, size_t v, double len, size_t num) {
    if (num == n || len >= answer)
        return len;
    used[v] = true;
    for (size_t i = 0; i < n; i++) {
        if (!used[i] || (i == INITIAL_VERTEX && num == n - 1)) {
            answer = min(answer, solve_brute_rec(graph, used, answer, n, i, len + graph[v][i], num + 1));
        }
    }
    used[v] = false;
    return answer;
}

// IDEA: grouping (just like sqrt-decomposition (https://habrahabr.ru/post/151151)
// IDEA: greedy approximation
// IDEA: ant algorithm (ACS-Q is good)
// FIXME return path?
double solve_brute(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v, double len, size_t num) {
    vector<bool> used(n);
    double answer = INF;
    return solve_brute_rec(graph, used, answer, n, v, len, num);
}
