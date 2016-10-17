#include <vector>
#include "helpers.h"

using namespace std;

void Helpers::get_euler_cycle_rec(const vector<vector<size_t>>& tree, size_t v, vector<size_t>& answer) {
    answer.push_back(v);
    for (size_t u: tree[v]) {
        get_euler_cycle_rec(tree, u, answer);
        answer.push_back(v);
    }
}

vector<size_t> Helpers::get_euler_cycle(const vector<vector<size_t>>& tree, size_t v) {
    vector<size_t> answer;
    get_euler_cycle_rec(tree, v, answer);
    return answer;
}
