// -*- compile-command: "make d11" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int m, n;

int flash(int i, int j, vector<vector<int>>& mat, set<pair<int,int>>& seen) {
    if (i < 0 || j < 0 || i >= m || j >= n || seen.count({i, j})) return 0;
    ++mat[i][j];
    if (mat[i][j] > 9) {
        mat[i][j] = 0;
        seen.insert({i, j});
        return 1 +
                flash(i+1, j, mat, seen) +
                flash(i+1, j+1, mat, seen) +
                flash(i+1, j-1, mat, seen) +
                flash(i, j+1, mat, seen) +
                flash(i, j-1, mat, seen) +
                flash(i-1, j, mat, seen) +
                flash(i-1, j+1, mat, seen) +
                flash(i-1, j-1, mat, seen);
    }
    return 0;
}

int step(vector<vector<int>>& mat) {
    set<pair<int,int>> seen;
    int res = 0;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (!seen.count({i, j}))
                res += flash(i, j, mat, seen);
    return res;
}

int main(int argc, char *argv[]) {
    vector<vector<int>> mat;
    string line;
    while (getline(cin, line)) {
        vector<int> row;
        for (char const &c: line)
            row.push_back(c-'0');
        mat.push_back(row);
    }
    m = mat.size(), n = mat[0].size();

    int res = 0, reps = 100;
    while (reps--)
        res += step(mat);

    cout << res << endl;
    return 0;
}
