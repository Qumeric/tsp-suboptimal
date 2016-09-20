#ifndef SOLVER_H
#define SOLVER_H

#include "constants.h"

#define cerr if (false) cerr

#define X first
#define Y second

using namespace std;

typedef pair<double, double> Point;

extern double graph[MAX_SIZE][MAX_SIZE];
extern vector<Point> points;
extern ofstream fout;

extern size_t ITER_COUNT;
extern double ALPHA; // zero for greedy
extern double BETA; // zero for crazy
extern double Q;
extern double FORGET;
extern double MAX_PHEROMONE_INIT;


void print_tree(vector<vector<size_t>>& tree, size_t v = 0, size_t margin = 0);
void get_euler_cycle(vector<vector<size_t>>& tree, size_t v, vector<size_t>& answer);
vector<vector<size_t>> get_mst(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v, const vector<size_t> &banned = {});
double solve_optimal20(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v = INITIAL_VERTEX);
//vector<size_t> gen_random_cycle(double graph[MAX_SIZE][MAX_SIZE], size_t n);
double solve_branch_and_bound(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v = INITIAL_VERTEX, double w = 0, size_t beg = INITIAL_VERTEX);
#endif

