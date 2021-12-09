// -*- compile-command: "make d9" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int m, n;

bool lowpoint(int i, int j, vector<vector<int>>& mat) {
    bool res = true;
    for (auto& d : dirs) {
        int x = i + d[0], y = j + d[1];
        if (x >= 0 && y >= 0 && x < m && y < n && mat[x][y] <= mat[i][j])
            res = false;
    }
    return res;
}

int dfs(int i, int j, int prev, int bid, vector<vector<int>>& mat) {
    if (i < 0 || j < 0 || i >= m || j >= n || mat[i][j] <= prev ||
        mat[i][j] == 9) return 0;
    mat[i][j] = bid;
    int p = mat[i][j];
    return 1 +
            dfs(i+1, j, p, bid, mat) +
            dfs(i-1, j, p, bid, mat) +
            dfs(i, j+1, p, bid, mat) +
            dfs(i, j-1, p, bid, mat);
}

int main(int argc, char *argv[]) {
    vector<vector<int>> mat;
    string line;
    while (getline(cin, line)) {
        vector<int> row(line.size());
        for (size_t i = 0; i < line.size(); ++i)
            row[i] = line[i] - '0';
        mat.push_back(row);
    }

    vector<int> basins;
    m = mat.size(), n = mat[0].size();
    int b = -1;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (mat[i][j] >= 0 && lowpoint(i, j, mat))
                basins.push_back(dfs(i, j, mat[i][j]-1, b--, mat));

    sort(basins.rbegin(), basins.rend());
    int res = basins[0] * basins[1] * basins[2];
    cout << res << endl;
    return 0;
}
