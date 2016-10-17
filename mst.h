#ifndef __MST_H__
#define __MST_H__

#include "constants.h"

using namespace std;

void print_tree(vector<vector<size_t>>& tree, size_t v = 0, size_t margin = 0);

static double dummy_len = 0; // FIXME
vector<vector<size_t>> get_mst(double graph[MAX_SIZE][MAX_SIZE], size_t v, size_t n, double &len = dummy_len, const vector<size_t> &banned = vector<size_t>());
#endif /*__MST_H__*/
