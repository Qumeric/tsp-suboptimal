#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "solver.h"

using namespace std;

double graph[MAX_SIZE][MAX_SIZE];
vector<Point> points;
ofstream fout;

//bool used[100000]; // FIXME use something saner? and not global

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

double solve_cn_rec(double graph[MAX_SIZE][MAX_SIZE], vector<bool>& used, size_t n, size_t v, double len) { // FIXME output graph
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
    fout << ";" << endl;
    return answer;
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

    // FIXME check correctness
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

double calc_length(double graph[MAX_SIZE][MAX_SIZE], vector<size_t>& cycle) {
    double ans = graph[cycle.back()][cycle.front()];
    for (int i = 0; i < cycle.size()-1; i++) {
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
    cerr << "GOT CYCLE" << endl;
    double d = calc_length(graph, cycle);
    cerr << "CALCED LENGTH" << endl;
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

// FIXME DIIIIRTY
vector<size_t> path;
bool used[MAX_SIZE]; // Fixme
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
    for (int i = 0; i < n; i++) {
        if (i != 0)
            prob[i] += prob[i-1];
        if (!used[i]) {
            prob[i] += pow(1.0/graph[v][i], BETA) * pow(phero[v][i], ALPHA);
        }
    }

    // consider elite ants?
    double var = get_random(prob[n-1]);

    for (int i = 0; i < n; i++) {
        if (var < prob[i]) {
            return rec_ant(graph, n, i, used, path, beg, dist + graph[v][i], cnt+1);
        }
    }

}

double solve_ant(double graph[MAX_SIZE][MAX_SIZE], size_t n) {
    double ans = 1e9;
    vector<bool> used(n);
    vector<size_t> path;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            phero[i][j] = get_random(1, MAX_PHEROMONE_INIT);
        }
    }
    size_t v;
    for (int iter = 0; iter < ITER_COUNT; iter++) {
        v = rand()%n;
        double len = rec_ant(graph, n, v, used, path, v);
        ans = min(ans, len);
        phero[path[0]][path[n]] *= (1-FORGET);
        phero[path[0]][path[n]] += Q/len;
        for (int i = 0; i < n; i++) {
            phero[path[i]][path[i+1]] *= (1-FORGET);
            phero[path[i]][path[i+1]] += Q/len;
        }
        path.clear();
        fill(used.begin(), used.end(), false);
    }
    return ans;
}
