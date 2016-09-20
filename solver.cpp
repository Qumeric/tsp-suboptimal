#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "solver.h"

using namespace std;

double graph[MAX_SIZE][MAX_SIZE];
vector<Point> points;
ofstream fout;

void print_tree(vector<vector<size_t>>& tree, size_t v, size_t margin) {
    for(int i = 0; i < margin; i++) cerr << ' ';
    cerr << v << " = (" << points[v].X << ", " << points[v].Y << ")" << endl;
    for (size_t u: tree[v]) {
        print_tree(tree, u, margin+1);
    }
}

double LAST_MST_LEN = 0; // FIXME dirty
vector<vector<size_t>> get_mst(double graph[MAX_SIZE][MAX_SIZE], size_t v, size_t n, const vector<size_t> &banned) {
    vector<bool> used(n);
    vector<pair<double, double>> dist(n);
    vector<vector<size_t>> mst(n);
    double len = 0; // FIXME do i need it?

    used[v] = true;
    //for (size_t u: banned)
    //    used[u] = true;

    for (size_t i = 0; i < n; i++)
        dist[i] = {graph[v][i], v};

    double ans = 0;
    for(size_t k = 1; k < n-banned.size(); k++) {
        size_t i = 0;
        while(used[i]) ++i;
        size_t nxt = i;
        while(++i < n)
            if (!used[i] && dist[i].first < dist[nxt].first)
                nxt = i;
        used[nxt] = true;
        len += dist[nxt].first;
        mst[dist[nxt].second].push_back(nxt);
        cerr << "add  mst edge: " << dist[nxt].second << ' ' << nxt << endl;
        for (size_t i = 0; i < n; i++) {
            if (graph[nxt][i] < dist[i].first)
                dist[i] = {graph[nxt][i], nxt};
        }
    }

    cerr << "MST: " << endl;
    print_tree(mst, v);

    LAST_MST_LEN = len;

    cerr << "MST length is " << len << endl;

    return mst;
}


void get_euler_cycle(vector<vector<size_t>>& tree, size_t v, vector<size_t>& answer) {
    cerr << "GET EULER CYCLE CALL " << v <<  endl;
    answer.push_back(v);
    for (size_t u: tree[v]) {
        get_euler_cycle(tree, u, answer);
        answer.push_back(v);
    }
}

double solve_optimal20(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v) {
    vector<vector<size_t>> mst = get_mst(graph, v, n);
    vector<size_t> euler_cycle;
    get_euler_cycle(mst, v, euler_cycle); // FIXME inconsistent interface?

    cerr << "EULER CYCLE: " << endl;
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


// FIXME DIIIIRTY
vector<size_t> path;
bool used[MAX_SIZE]; // FIXME
double ans = 1e9; // FIXME use first approx
vector<size_t> anspath;
double solve_branch_and_bound(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v, double w, size_t beg) {
    used[v] = true;
    path.push_back(v);
    bool found = false;
    if (v == beg) {
        get_mst(graph, v, n);
        ans = LAST_MST_LEN * 1.5; // it's know that 1.5-optimal solution exists
    }

    int mst_init = -1;

    // FIXME one vertex problem
    double shortestA = 1e9, shortestB = 1e9;
    for (int i = 0; i < n; i++) {
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
        get_mst(graph, mst_init, n, path);
        cerr << "DONE!" << endl;
    }

    for (int i = 0; i < n; i++) { // FIXME randomized/sorted
        if (!used[i]) {
            found = true;
            if (w + shortestA + shortestB + LAST_MST_LEN < ans) {
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
