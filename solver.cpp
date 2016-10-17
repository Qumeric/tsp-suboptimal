#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "mst.h"
#include "solver.h"
#include "helpers.h"

using namespace std;

vector<Point> points;
ofstream fout;

double graph[MAX_SIZE][MAX_SIZE];

double solve_optimal20(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v) {
    vector<vector<size_t>> mst = get_mst(graph, v, n);
    vector<size_t> euler_cycle = Helpers::get_euler_cycle(mst, v);

    for (size_t u: euler_cycle) {
        cerr << u << ' ';
    } cerr << endl;

    double answer = 0;

    vector<bool> used(n);
    size_t last = v;
    for(size_t i = 1; i < euler_cycle.size(); i++) {
        if (!used[euler_cycle[i]]) {
            fout << last << ' ' << euler_cycle[i] << endl;
            answer += graph[last][euler_cycle[i]];
            last = euler_cycle[i];
            used[euler_cycle[i]] = true;
        }
    }

    fout << ";" << endl;

    cerr << "SIZE OF EULER CYCLE IN MST IS " << euler_cycle.size() << endl;
    return answer;
}


// FIXME DIIIIRTY and doesn't really works
vector<size_t> path;
bool used[MAX_SIZE]; // FIXME
double ans = 1e9; // FIXME use first approx
vector<size_t> anspath;
double solve_branch_and_bound(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v, double w, size_t beg) {
    used[v] = true;
    path.push_back(v);
    bool found = false;
    double mst_len = 0;
    if (v == beg) {
        get_mst(graph, v, n, mst_len);
        ans = mst_len * 1.5; // it's known that 1.5-optimal solution exists
    }

    int mst_init = -1;

    // FIXME one vertex problem
    double shortestA = 1e9, shortestB = 1e9;
    for (size_t i = 0; i < n; i++) {
        if (used[i]) continue;
        if (graph[beg][i] < shortestA) {
            shortestA = graph[beg][i];
            mst_init = i;
        }
        shortestB = min(shortestB, graph[v][i]);
    }

    if (mst_init >= 0) {
        cerr << "We are going to find mst from " << mst_init << " and with this path: ";
        for (size_t u: path) cerr << u << ' '; cerr << endl;
        get_mst(graph, mst_init, n, mst_len, path);
        cerr << "DONE!" << endl;
    }

    for (size_t i = 0; i < n; i++) { // FIXME randomized/sorted
        if (!used[i]) {
            found = true;
            if (w + shortestA + shortestB + mst_len < ans) {
                solve_branch_and_bound(graph, n, i, w + graph[v][i]);
            }
        }
    }
    if (!found) {
        if (w + graph[v][beg] < ans) {
            ans = w + graph[v][beg];
            anspath = path;
        }
    }
    path.pop_back();
    used[v] = false;
    return ans;
}
