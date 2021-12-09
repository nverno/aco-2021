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

int main(int argc, char *argv[]) {
    vector<vector<int>> mat;
    string line;
    while (getline(cin, line)) {
        vector<int> row(line.size());
        for (size_t i = 0; i < line.size(); ++i)
            row[i] = line[i] - '0';
        mat.push_back(row);
    }

    int res = 0;
    m = mat.size(), n = mat[0].size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lowpoint(i, j, mat))
                res += mat[i][j] + 1;
        }
    }

    cout << res << endl;
    return 0;
}
