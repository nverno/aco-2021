// -*- compile-command: "make d6" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    vector<vector<int>> grid(1000, vector<int>(1000));
    vector<string> parts;
    vector<int> r1, r2;

    string line;
    while (getline(cin, line)) {
        split(line, parts);

        string cmd = parts[0], dir;
        if (cmd == "turn") {
            dir = parts[1];
            split(parts[2], r1, ',');
            split(parts[4], r2, ',');
        } else {
            split(parts[1], r1, ',');
            split(parts[3], r2, ',');
        }

        int x1 = r1[0], x2 = r2[0], y1 = r1[1], y2 = r2[1],
            dx = dir.empty() ? -1 : dir == "on" ? 1 : 0;
        for (int i = x1; i <= x2; ++i) {
            for (int j = y1; j <= y2; ++j) {
                if (dx == -1)
                    grid[i][j] ^= 1;
                else
                    grid[i][j] = dx;
            }
        }
    }

    int res = 0;
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            res += grid[i][j];
        }
    }
    cout << res << endl;
    
    return 0;
}
