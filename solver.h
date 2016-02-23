#ifndef SOLVER_H
#define SOLVER_H

#define cerr if (false) cerr

#define X first
#define Y second

using namespace std;

typedef pair<double, double> Point;

const double INF = 1e18;
const size_t INITIAL_VERTEX = 0;
const size_t MAX_SIZE = 10000;
const double MAX_CORD = 1000;
extern double graph[MAX_SIZE][MAX_SIZE];
extern vector<Point> points;
extern ofstream fout;

// FIXME
extern size_t ITER_COUNT;
extern double ALPHA; // zero for greedy
extern double BETA; // zero for crazy
extern double Q;
extern double FORGET;
extern double MAX_PHEROMONE_INIT;

inline double get_random(double max_cord, double min_cord = 0) {
    static mt19937_64 eng(time(0));
    uniform_real_distribution<double> unif(min_cord, max_cord);
    return unif(eng);
}

void print_tree(vector<vector<size_t>>& tree, size_t v = 0, size_t margin = 0);
double solve_cn(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v = INITIAL_VERTEX, double len = 0);
double solve_brute(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v = INITIAL_VERTEX, double len = 0, size_t num = 0); // FIXME saner
void get_euler_cycle(vector<vector<size_t>>& tree, size_t v, vector<size_t>& answer);
vector<vector<size_t>> get_mst(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v, const vector<size_t> &banned = {});
double solve_optimal20(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v = INITIAL_VERTEX);
double solve_annealing(double graph[MAX_SIZE][MAX_SIZE], size_t n);
vector<size_t> gen_random_cycle(double graph[MAX_SIZE][MAX_SIZE], size_t n);
double solve_branch_and_bound(double graph[MAX_SIZE][MAX_SIZE], size_t n, size_t v = INITIAL_VERTEX, double w = 0, size_t beg = INITIAL_VERTEX);
double solve_ant(double graph[MAX_SIZE][MAX_SIZE], size_t n);
#endif
