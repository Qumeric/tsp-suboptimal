#include <ISolver.h>
#include <ChristofidesSolver.h>
#include <MST.h>
#include <cassert>
#include <Helpers.h>

using std::vector;
using std::set;

double ChristofidesSolver::solve(size_t initial_vertex) {
    vector<vector<size_t>> mst = MST(g, initial_vertex).toAdjList();
    set<size_t> oddDegreeVertices = findOddDegree(mst);
    set<Edge> matching = findMinimumPerfectMatching(oddDegreeVertices);
    for (const Edge &edge: matching) {
        mst[edge.from].push_back(edge.to);
        mst[edge.to].push_back(edge.from);
    }
    vector<size_t> eulerCycle = Helpers::get_euler_cycle(mst, initial_vertex);
    // Now do the shortcutting FIXME
}

set<size_t> ChristofidesSolver::findOddDegree(const vector<vector<size_t>> &adjList) {
    set<size_t> oddDegreeVertices;
    for (size_t i = 0; i < adjList.size(); i++) {
        if (adjList[i].size() % 2 == 1) {
            oddDegreeVertices.insert(i);
        }
    }
    assert(oddDegreeVertices.size() % 2 == 0); // By the handshaking lemma FIXME is assert ok?

    return oddDegreeVertices;
}

set<Edge> ChristofidesSolver::findGreedyPerfectMatching(set<size_t> vertices) {
    set<Edge> matching;
    size_t closest;
    double length;
    std::set<size_t>::iterator tmp, first;

    while (!vertices.empty()) {
        first = vertices.begin();
        length = std::numeric_limits<size_t>::max();
        for (auto it = std::next(first); it != vertices.end(); it++) {
            if (g.getDistance(*first, *it) < length) {
                length = g.getDistance(*first, *it);
                closest = *it;
                tmp = it;
            }
        }
        vertices.erase(tmp);
        vertices.erase(first);
        matching.insert({closest, *first});
    }
    return matching;
}

/**
 * Find the minimum perfect matching on given set of vertices
 * @param vertices vertices to find the minimum perfect matching on (should have odd size)
 * @return Minimum perfect matching (as set of edges)
 */
set<Edge> ChristofidesSolver::findMinimumPerfectMatching(set<size_t> vertices) {
    return findGreedyPerfectMatching(vertices); // FIXME
}