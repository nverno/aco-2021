// -*- compile-command: "make d15" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int upper(vector<vector<int>>& mat) {
    const int m = mat.size(), n = mat[0].size();
    vector<vector<int>> dp(m, vector<int>(n));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            dp[i][j] = mat[i][j];
            int nxt = INT_MAX;
            if (i > 0) nxt = dp[i-1][j];
            if (j > 0) nxt = min(nxt, dp[i][j-1]);
            if (nxt != INT_MAX)
                dp[i][j] += nxt;
        }
    }
    return dp[m-1][n-1];
}

void incr(vector<vector<int>>& mat) {
    for (size_t i = 0; i < mat.size(); ++i) {
        for (size_t j = 0; j < mat[0].size(); ++j) {
            mat[i][j] = 1 + mat[i][j]%9;
        }
    }
}

int main(int argc, char *argv[]) {
    vector<vector<int>> mm, mmm, mat;
    string line;
    while (getline(cin, line)) {
        vector<int> row;
        for (auto& c : line)
            row.push_back(c-'0');
        if (row.size())
            mm.push_back(row);
    }

    mmm = mm;
    for (int t = 0; t < 4; ++t) {
        incr(mm);
        for (size_t i = 0; i < mm.size(); ++i)
            mmm[i].insert(mmm[i].end(), mm[i].begin(), mm[i].end());
    }
    mat = mmm;
    for (int t = 0; t < 4; ++t) {
        incr(mmm);
        for (size_t i = 0; i < mmm.size(); ++i)
            mat.push_back(mmm[i]);
    }

    const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    const size_t m = mat.size(), n = mat[0].size();
        
    int lim = upper(mat);
    vector<int> best(m * n, lim);
    std::priority_queue<pair<int,int>, vector<pair<int,int>>> pq;
    
    pq.push({ 0, 0 });
    best[0] = 0;
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

    cout << best[(m-1)*n + n-1] + mat[m-1][n-1] - mat[0][0] << endl;
    return 0;
}
