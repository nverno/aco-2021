// -*- compile-command: "make d25" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int SOUTH = 1, EAST = 2;
vector<string> mat;
queue<pair<int,int>> east, south;
size_t m, n;

pair<int,int> getNext(pair<int,int>& p, int dir) {
    auto [x, y] = p;
    if (dir == SOUTH) return {(x+1)%m, y};
    return {x, (y+1)%n};
};

int move(int dir) {
    auto& ps = dir == SOUTH ? south : east;
    vector<pair<int,int>> nxt;
    int sz = ps.size();
    while (sz--) {
        auto cur = ps.front(); ps.pop();
        auto [xx, yy] = getNext(cur, dir);
        if (mat[xx][yy] == '.') {
            nxt.push_back(cur);
            ps.push({xx, yy});
        } else
            ps.push(cur);
    }
    for (auto& p : nxt) {
        auto [x, y] = p;
        auto [xx, yy] = getNext(p, dir);
        swap(mat[xx][yy], mat[x][y]);
    }
    return nxt.size();
};

int main(int argc, char *argv[]) {
    string line;
    size_t i = 0;
    while (getline(cin, line)) {
        mat.push_back(line);
        for (size_t j = 0; j < line.size(); ++j) {
            if (line[j] == '>') east.push({ i, j });
            else if (line[j] == 'v') south.push({ i, j });
        }
        ++i;
    }
    m = mat.size(), n = mat[0].size();

    int res = 1, cnt;
    while ((cnt = move(EAST) + move(SOUTH)) != 0)
        ++res;

    cout << res << endl;
    
    return 0;
}
