#ifndef TSP_SUBOPTIMAL_EDGE_H
#define TSP_SUBOPTIMAL_EDGE_H

struct Edge {
    size_t from, to;
    double length;

    bool operator<(const Edge &e) const {
        return from < e.from || (from == e.from && to < e.to);
    }
};

#endif // TSP_SUBOPTIMAL_EDGE_H
