// -*- compile-command: "make d8" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int m, n;
vector<vector<int>> grid, vis;

void transpose() {
    vector<vector<int>> ngrid(m, vector<int>(n)), nvis(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ngrid[j][i] = grid[i][j];
            nvis[j][i] = vis[i][j];
        }
    }
    swap(grid, ngrid);
    swap(vis, nvis);
    swap(m, n);
}

void check_row(int i) {
    auto& r = grid[i], &v = vis[i];
    stack<int> st;
    for (int j = 0; j < n; ++j) {
        while (!st.empty() && r[st.top()] < r[j])
            st.pop();
        if (st.empty()) v[j] |= 1;
        st.push(j);
    }
}

void check_visible() {
    for (int i = 0; i < m; ++i) {
        check_row(i);
        reverse(grid[i].begin(), grid[i].end());
        reverse(vis[i].begin(), vis[i].end());
        check_row(i);
    }
}

int main(int argc, char *argv[]) {
    string line;
    while (cin >> line) {
        vector<int> row;
        for (auto& x : line) 
            row.push_back(x - '0');
        grid.push_back(row);
    }
    m = grid.size();
    n = grid[0].size();
    vis.resize(m, vector<int>(n));

    check_visible();
    transpose();
    check_visible();

    int res = 0;
    for (auto& r : vis) 
        res += accumulate(r.begin(), r.end(), 0);
    cout << res << '\n';
    return 0;
}
