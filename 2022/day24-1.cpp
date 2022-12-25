// -*- compile-command: "make d24" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

using bs = bitset<128>;

const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main(int argc, char *argv[]) {
    vector<string> grid;
    string line;
    getline(cin, line);
    while (getline(cin, line)) {
        int n = line.size();
        grid.push_back(line.substr(1, n-2));
    }
    grid.pop_back();

    const int m = grid.size(), n = grid[0].size();
    vector<vector<pair<bs,bs>>> occupied(m, vector<pair<bs,bs>>(n));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            char c = grid[i][j];
            if (c == '<' || c == '>') {
                int dx = c == '<' ? -1 : 1;
                for (int k = 1; k <= n; ++k) 
                    occupied[i][(j+n+dx*k)%n].first[k] = 1;
            } else if (c == 'v' || c == '^') {
                int dy = c == 'v' ? 1 : -1;
                for (int k = 1; k <= m; ++k) 
                    occupied[(i+m+dy*k)%m][j].second[k] = 1;
            }
            grid[i][j] = '.';
        }
    }

    // cout << '\n';
    // for (auto& r : grid) {
    //     cout << r << '\n';
    // }
    // cout << '\n';
    
    // cout << occupied[0][0].first.to_string() << '\n';
    // cout << occupied[0][0].second.to_string() << '\n';

    pair<int,int> start = {-1, -1};
    queue<pair<int,int>> q;
    set<pair<int,pair<int,int>>> seen;
    seen.insert({0, start});
    q.push(start);

    auto avail = [&](int i, int j, int s) {
        return !(occupied[i][j].first[s%n] || occupied[i][j].second[s%m]);
    };

    int steps = 0;
    bool done = false;
    while (!(done || q.empty())) {
        int sz = q.size(),
            ns = steps + 1;
        
        while (sz--) {
            auto [i, j] = q.front(); q.pop();
            if (i == m-1 && j == n-1) {
                done = true;
                break;
            }
            if (i == -1) {
                if (!seen.count({ns, {0,0}}) && avail(0, 0, ns)) {
                    seen.insert({ns, {0,0}});
                    q.push({0, 0});
                }
                q.push(start);
            } else {
                if (!seen.count({ns, {i, j}}) && avail(i, j, ns)) {
                    seen.insert({ns, {i, j}});
                    q.push({i, j});
                }
                for (auto& d : dirs) {
                    int x = i + d[0], y = j + d[1];
                    if (x >= 0 && y >= 0 && x < m && y < n && !seen.count({ns, {x, y}}) && avail(x, y, ns)) {
                        seen.insert({ns, {x, y}});
                        q.push({x, y});
                    }
                }
            }
        }
        ++steps;
    }

    cout << steps << '\n';
    return 0;
}
