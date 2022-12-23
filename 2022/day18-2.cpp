// -*- compile-command: "make d18" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

using point = tuple<int,int,int>;
set<point> ps;

const vector<point> dirs = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
array<int,2> mx = {INT_MAX, INT_MIN}, my = {INT_MAX, INT_MIN}, mz = {INT_MAX, INT_MIN};

bool contained(point p, set<point>& seen) {
    if (ps.count(p) || seen.count(p)) return true;
    auto [x, y, z] = p;
    if (x > mx[1] || x < mx[0] || y > my[1] || y < my[0] || z > mz[1] || z < mz[0])
        return false;
    seen.insert(p);
    for (auto& [dx, dy, dz] : dirs) {
        point pp = {x+dx, y+dy, z+dz};
        if (!seen.count(pp) && !contained(pp, seen)) return false;
        seen.insert(pp);
    }
    return true;
}

void update_lims(vector<int>& vs) {
    int x = vs[0], y = vs[1], z = vs[2];
    mx[0] = min(x, mx[0]);
    mx[1] = max(x, mx[1]);
    my[0] = min(y, my[0]);
    my[1] = max(y, my[1]);
    mz[0] = min(z, mz[0]);
    mz[1] = max(z, mz[1]);
}

int main(int argc, char *argv[]) {
    string line;
    while (getline(cin, line)) {
        vector<int> vals;
        split(line, vals, ',');
        ps.insert({vals[0], vals[1], vals[2]});
        update_lims(vals);
    }

    int res = 0;
    for (auto& [x,y,z] : ps) {
        for (auto& [dx, dy, dz] : dirs) {
            set<point> seen;
            point p = {x+dx, y+dy, z+dz};
            if (!contained(p, seen))
                ++res;
        }
    }

    cout << res << '\n';
    return 0;
}
