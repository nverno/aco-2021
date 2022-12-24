// -*- compile-command: "make d22" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const string direction = "NESW";
const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int di(char d) { return direction.find(d); }

char turn(char cur, char dir) {
    int i = di(cur);
    return direction[(i + 4 + (dir == 'L' ? -1 : 1)) % 4];
}

int main(int argc, char *argv[]) {
    vector<string> grid;
    vector<int> dist;

    string line, path = "R";  // start facing east
    while (getline(cin, line)) {
        if (line.empty()) {
            getline(cin, line);
            int sz = line.size();
            for (int i = 0; i < sz; ++i) {
                if (isdigit(line[i])) {
                    int v = 0;
                    while (i < sz && isdigit(line[i])) {
                        v = 10*v + (line[i] - '0');
                        ++i;
                    }
                    --i;
                    dist.push_back(v);
                }
                else path += line[i];
            }
            assert(path.size() == dist.size());
        }
        else grid.push_back(line);
    }

    int m = grid.size();
    vector<int> st(m), en(m);
    int maxw = 0;
    for (int i = 0; i < m; ++i) {
        auto& r = grid[i];
        int sz = r.size(), j = 0;
        while (j < sz && r[j] == ' ') ++j;
        st[i] = j;
        while (j < sz && r[j] != ' ') ++j;
        en[i] = j;
        maxw = max(maxw, en[i]);
    }

    // pad rows
    for (auto& r : grid) 
        if (maxw > (int)r.size()) 
            r += string(maxw - r.size(), ' ');

    int n = grid[0].size();
    vector<int> top(n), bot(n);
    for (int j = 0; j < n; ++j) {
        int i = 0;
        while (i < m && grid[i][j] == ' ') ++i;
        top[j] = i;
        while (i < m && grid[i][j] != ' ') ++i;
        bot[j] = i;
    }
    
    int plen = path.size(),
       ci = 0,
       cj = st[0];
    char dir = 'E';
    
    for (int pi = 0; pi < plen; ++pi) {
        if (pi > 0) dir = turn(dir, path[pi]);
        auto [dy, dx] = dirs[di(dir)];

        int d = dist[pi];
        while (d--) {
            grid[ci][cj] = dir == 'E' ? '>' : dir == 'W' ? '<' : dir == 'S' ? 'v' : '^';

            int ii = ci + dy, jj = cj + dx;

            // board wraps around
            if (jj == en[ci]) jj = st[ci];
            else if (jj < st[ci]) jj = en[ci]-1;

            if (ii >= bot[cj]) ii = top[cj];
            else if (ii < top[cj]) ii = bot[cj]-1; 
            
            if (grid[ii][jj] == '#') 
                break;

            ci = ii;
            cj = jj;
        }
    }

    int facing = dir == 'E' ? 0 : dir == 'S' ? 1 : dir == 'W' ? 2 : 3,
           res = 1000 * (ci + 1) + 4 * (cj + 1) + facing;

    // cout << '\n';
    // for (auto& r : grid) {
    //     cout << r << '\n';
    // }

    cout << res << '\n';

    return 0;
}
