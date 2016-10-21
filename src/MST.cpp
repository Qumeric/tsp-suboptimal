#include <vector>
#include <iostream>
#include <MST.h>

/**
 * Prim's algorithm
 */
MST::MST(const Graph &g, size_t initial_vertex, const vector<size_t> &banned) {
    size_t n = g.getSize();
    vector<bool> used(n);
    // {minimal distance from observed set ([v from g | used[v] == true]), closest vertex from observed set}
    vector<std::pair<double, size_t>> dist(n);
    mst.resize(n);
    length = 0;

    used[initial_vertex] = true;

    for (size_t i = 0; i < n; i++)
        dist[i] = {g.getDistance(initial_vertex, i), initial_vertex};

    for (size_t k = 1; k < n - banned.size(); k++) {
        size_t i = 0;
        while (used[i]) ++i;
        size_t nxt = i;
        while (++i < n)
            if (!used[i] && dist[i].first < dist[nxt].first)
                nxt = i;
        used[nxt] = true;
        length += dist[nxt].first;
        mst[dist[nxt].second].push_back(nxt);
        for (size_t j = 0; j < n; j++) {
            if (g.getDistance(nxt, j) < dist[j].first)
                dist[j] = {g.getDistance(nxt, j), nxt};
        }
    }
}

double MST::getLength() const {
    return length;
}

vector<vector<size_t>> MST::toAdjList() const {
    return mst;
}