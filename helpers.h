#ifndef __HELPERS_H__
#define __HELPERS_H__

using namespace std;

class Helpers {
public:
    static vector<size_t> get_euler_cycle(const vector<vector<size_t>>& tree, size_t v);
private:
    static void get_euler_cycle_rec(const vector<vector<size_t>>& tree, size_t v, vector<size_t>& answer);
};

#endif /*__HELPERS_H__*/
