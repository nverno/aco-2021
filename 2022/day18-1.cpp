// -*- compile-command: "make d18" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

using point = tuple<int,int,int>;
set<point> ps;

const vector<point> dirs = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};

int main(int argc, char *argv[]) {
    string line;
    while (getline(cin, line)) {
        vector<int> vals;
        split(line, vals, ',');
        ps.insert({vals[0], vals[1], vals[2]});
    }

    // set<point> edge;
    int res = 0;
    for (auto& [x,y,z] : ps) {
        for (auto& [dx, dy, dz] : dirs) {
            if (!ps.count({x+dx, y+dy, z+dz})) {
                ++res;
                // edge.insert({x+dx, y+dy, z+dz});
                // nps.insert({x+dx, y+dy, z+dz});
            }
        }
    }
    // for (auto& [x,y,z] : edge) {
    //     cout << x << "," << y << "," << z << '\n';
    // }
    cout << res << '\n';
    return 0;
}
