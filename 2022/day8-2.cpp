// -*- compile-command: "make d8" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int m, n;
vector<vector<int>> grid, score;

void transpose() {
    vector<vector<int>> ngrid(m, vector<int>(n)), nscore(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            ngrid[j][i] = grid[i][j];
            nscore[j][i] = score[i][j];
        }
    }
    swap(grid, ngrid);
    swap(score, nscore);
    swap(m, n);
}

void score_row(int i) {
    auto& r = grid[i], &v = score[i];
    stack<int> st;
    for (int j = 0; j < n; ++j) {
        while (!st.empty() && r[st.top()] < r[j])
            st.pop();
        v[j] *= st.empty() ? j : j - st.top();
        st.push(j);
    }
}

void row_scores() {
    for (int i = 0; i < m; ++i) {
        score_row(i);
        reverse(grid[i].begin(), grid[i].end());
        reverse(score[i].begin(), score[i].end());
        score_row(i);
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
    score.resize(m, vector<int>(n, 1));

    row_scores();
    transpose();
    row_scores();

    int res = 0;
    for (auto& r : score) 
        res = max(res, *max_element(begin(r), end(r)));
    cout << res << '\n';
    return 0;
}
