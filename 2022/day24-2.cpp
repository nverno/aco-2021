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

    auto avail = [&](int i, int j, int s) {
        return !(occupied[i][j].first[s%n] || occupied[i][j].second[s%m]);
    };

    auto bfs = [&](pair<int,int> start, pair<int,int> goal, int time) {
        pair<int,int> first = start.first == -1 ? make_pair(0, 0) : make_pair(m-1, n-1);
        queue<pair<int,int>> q;
        set<pair<int,pair<int,int>>> seen;
        seen.insert({time, start});
        q.push(start);
        
        int steps = time;
        bool done = false;
        while (!(done || q.empty())) {
            int sz = q.size(),
                ns = steps + 1;
        
            while (sz--) {
                auto [i, j] = q.front(); q.pop();
                if (i == goal.first && j == goal.second) {
                    done = true;
                    break;
                }
                if (start.first && j == start.second) {
                    if (!seen.count({ns, first}) && avail(first.first, first.second, ns)) {
                        seen.insert({ns, first});
                        q.push(first);
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
        return steps;
    };

    int a = bfs({-1,-1}, {m-1, n-1}, 0),
        b = bfs({m, n}, {0, 0}, a),
        c = bfs({-1,-1}, {m-1, n-1}, b);

    cout << a << ", " << (b-a) << ", " << (c-b) << ": " << c << '\n';
    return 0;
}
