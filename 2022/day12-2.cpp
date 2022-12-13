// -*- compile-command: "make d12" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main(int argc, char *argv[]) {
    vector<string> g;
    pair<int,int> goal;
    string line;
    while (cin >> line) 
        g.push_back(line);

    const int m = g.size(), n = g[0].size();
    queue<pair<int,int>> q;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == 'E') {
                g[i][j] = 'z';
                q.push({i, j});
            }
            else if (g[i][j] == 'S') {
                g[i][j] = 'a';
            }
        }
    }

    vector<vector<int>> moves(m, vector<int>(n, m*n));
    auto [si, sj] = q.front();
    moves[si][sj] = 0;
    int res = m*n;

    bool done = false;
    while (!(done || q.empty())) {
        int sz = q.size();
        while (sz--) {
            auto [i, j] = q.front(); q.pop();
            if (g[i][j] == 'a') {
                res = moves[i][j];
                done = true;
                break;
            }

            int mv = moves[i][j] + 1;
            for (auto& d : dirs) {
                int x = i + d[0], y = j + d[1];
                if (x >= 0 && y >= 0 && x < m && y < n && g[x][y] >= g[i][j]-1 && mv < moves[x][y]) {
                    q.push({x, y});
                    moves[x][y] = mv;
                }
            }
        }
    }

    cout << res << '\n';
    return 0;
}
