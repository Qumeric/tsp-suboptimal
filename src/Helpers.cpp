#include <vector>
#include "Helpers.h"

using namespace std;


#include <random>

double Helpers::get_random(double max_cord, double min_cord) {
    static std::mt19937_64 eng(time(0));
    std::uniform_real_distribution<double> unif(min_cord, max_cord);
    return unif(eng);
}

void Helpers::get_euler_cycle_rec(const vector<vector<size_t>> &tree, size_t v, vector<size_t> &answer) {
    answer.push_back(v);
    for (size_t u: tree[v]) {
        get_euler_cycle_rec(tree, u, answer);
        answer.push_back(v);
    }
}

vector<size_t> Helpers::get_euler_cycle(const vector<vector<size_t>> &tree, size_t v) {
    vector<size_t> answer;
    get_euler_cycle_rec(tree, v, answer);
    return answer;
}
