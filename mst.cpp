#include <vector>
#include <iostream>
#include "solver.h"
#include "mst.h"

using namespace std;

void print_tree(vector<vector<size_t>>& tree, size_t v, size_t margin) {
    for(size_t i = 0; i < margin; i++) cerr << ' ';
    cerr << v << " = (" << points[v].X << ", " << points[v].Y << ")" << endl;
    for (size_t u: tree[v]) {
        print_tree(tree, u, margin+1);
    }
}

vector<vector<size_t>> get_mst(double graph[MAX_SIZE][MAX_SIZE], size_t v, size_t n, double &len, const vector<size_t> &banned) {
    vector<bool> used(n);
    vector<Point> dist(n);
    vector<vector<size_t>> mst(n);
    len = 0;

    used[v] = true;

    for (size_t i = 0; i < n; i++)
        dist[i] = {graph[v][i], v};

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

    cerr << "MST length is " << len << endl;

    return mst;
}
