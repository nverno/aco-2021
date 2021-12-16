// -*- compile-command: "make d15" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    vector<vector<int>> mat;
    string line;
    while (getline(cin, line)) {
        vector<int> row;
        for (auto& c : line)
            row.push_back(c-'0');
        if (row.size())
            mat.push_back(row);
    }

    const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    const int m = mat.size(), n = mat[0].size();
    vector<int> best(m * n, INT_MAX);
    std::priority_queue<pair<int,int>, vector<pair<int,int>>> pq;

    pq.push({ 0, 0 });
    while (!pq.empty()) {
        auto [len, pos] = pq.top(); pq.pop();
        int i = pos/n, j = pos%n, v = mat[i][j] + len;
        for (auto& d : dirs) {
            int x = i + d[0], y = j + d[1], nxt = x*n + y;
            if (x >= 0 && y >= 0 && x < m && y < n && best[nxt] > v) {
                pq.push({ v, nxt });
                best[nxt] = v;
            }
        }
    }
    cout << best.back() << endl;
    return 0;
}
