#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

#include "solver.h"
#include "bruteforce.h"
#include "closestN.h"
#include "ant.h"
#include "annealing.h"
#include "mst.h"

using namespace std;

size_t n;

inline double distance(Point a, Point b) {
    return sqrt((a.X-b.X)*(a.X-b.X) + (a.Y-b.Y)*(a.Y-b.Y)); // FIXME not only Euclidean?
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        cout << "Usage ./salesman <number-of-points>" << endl;
        return 0;
    }
    fout.open("graph.txt");
    n = stoi(argv[1]);
    if (argc > 2) {
        ALPHA = stof(argv[2]);
        BETA = stof(argv[3]);
        Q = stof(argv[4]);
        FORGET = stof(argv[5]);
        MAX_PHEROMONE_INIT = stof(argv[6]);
    }
    points.resize(n);
    for (size_t i = 0; i < n; i++) {
        Point point = {get_random(MAX_CORD), get_random(MAX_CORD)}; // FIXME do something sane
        points[i] = point;
        cerr << "Point number " << i << " is (" << point.X << ", " << point.Y << ")" << endl;
        fout << point.X << ' ' << point.Y << endl;
    }
    fout << ";" << endl;

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            graph[i][j] = graph[j][i] = distance(points[i], points[j]);
        }
    }

    get_mst(graph, INITIAL_VERTEX, n);
    if (n < 12) { // 12! takes too much time
        cout << "Brute force have found this answer: " << solve_brute(graph, n) << endl;
        cout << "Branch and bound have found this answer: " << solve_branch_and_bound(graph, n) << endl;
    }
    if (argc<=2) {
        cout << "Annealing imitation have found this answer: " << solve_annealing(graph, n) << endl;
        cout << "2-OPT greedy solution have found this answer: " << solve_optimal20(graph, n) << endl;
        cout << "Closest neighbor have found this answer: " << solve_cn(graph, n) << endl;
        cout << "Ant algorithm have found this answer: " << solve_ant(graph, n) << endl;
    } else {
        cout << solve_ant(graph, n) << endl;
    }
}
