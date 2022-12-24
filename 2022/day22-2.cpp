// -*- compile-command: "make d22" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

// 50x50 cube
const int D = 50, // 4
    M = 3*D, N = 4*D;

const string direction = "NESW";
const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int di(char d) { return direction.find(d); }

char turn(char cur, char dir) {
    int i = di(cur);
    return direction[(i + 4 + (dir == 'L' ? -1 : 1)) % 4];
}

int region(int i, int j) {
    if (i < D) return 1;
    if (i < 2*D) return 2 + j/D;
    return 3 + j/D;
}

// FIXME: problem layout different than example
tuple<char,int,int> transition_east(int i, int j) {
    int r = region(i, j);
    switch (r) {
        case 1: return {'W', M-1-i, N-1};    // 6(<)
        case 4: return {'S', 2*D, 5*D-1-i};  // 6(v)
        case 6: return {'W', M-1-i, M-1};    // 2(>)
        default: cout << "east: " << i << "," << j << ", r=" << r << '\n'; assert(0);
    }
}
tuple<char,int,int> transition_west(int i, int j) {
    int r = region(i, j);
    switch (r) {
        case 1: return {'S', D, D+i};            // 3(v)
        case 2: return {'N', M-1, 2*D+i};        // 6(^)
        case 5: return {'N', 2*D-1, D+(M-i-1)};  // 3(^)
        default: cout << "west: " << i << "," << j << ", r=" << r << '\n'; assert(0);
    }
}
tuple<char,int,int> transition_south(int i, int j) {
    int r = region(i, j);
    switch (r) {
        case 2: return {'N', M-1, 3*D-1-j};    // 5(^)
        case 3: return {'E', 3*D-1-j, 2*D};    // 5(>)
        case 5: return {'N', 2*D-1, 3*D-1-j};  // 2(^)
        case 6: return {'N', D+N-1-j, 0};      // 2(>)
        default: cout << "south: " << i << "," << j << ", r=" << r << '\n'; assert(0);
    }
}
tuple<char,int,int> transition_north(int i, int j) {
    int r = region(i, j);
    switch (r) {
        case 1: return {'S', D, 3*D-1-j};      // 2(v)
        case 2: return {'S', 0, 3*D-1-j};      // 1(v)
        case 3: return {'W', j-D, 2*D};        // 1(>)
        case 6: return {'W', 5*D-1-j, 3*D-1};  // 4(<)
        default: cout << "north: " << i << "," << j << ", r=" << r << '\n'; assert(0);
    }
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

        int d = dist[pi];
        cout << "move: from " << ci <<"," << cj << " -> " << d << " units to the " << dir << '\n';
        while (d--) {
            auto [dy, dx] = dirs[di(dir)];
            grid[ci][cj] = dir == 'E' ? '>' : dir == 'W' ? '<' : dir == 'S' ? 'v' : '^';
            int ii = ci + dy, jj = cj + dx;
            
            // board wraps around
            tuple<char,int,int> nxt = {dir, ii, jj};
            if (jj >= en[ci]) {
                nxt = transition_east(ci, cj);
                // cout << "move east: (" << ci <<"," <<cj <<") -> (" << get<1>(nxt)<<","<<get<2>(nxt)<<")["<<get<0>(nxt)<<"]\n";
            } else if (jj < st[ci]) {
                nxt = transition_west(ci, cj);
            } else if (ii >= bot[cj]) {
                nxt = transition_south(ci, cj);
            } else if (ii < top[cj]) {
                nxt = transition_north(ci, cj);
            }
            
            auto [nd, ni, nj] = nxt;
            if (grid[ni][nj] == '#') 
                break;
            dir = nd;
            ci = ni;
            cj = nj;
        }
    }

    int facing = dir == 'E' ? 0 : dir == 'S' ? 1 : dir == 'W' ? 2 : 3,
           res = 1000 * (ci + 1) + 4 * (cj + 1) + facing;

    cout << '\n';
    for (auto& r : grid) {
        cout << r << '\n';
    }
    cout << res << '\n';

    return 0;
}
