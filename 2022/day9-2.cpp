// -*- compile-command: "make d9" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int SZ = 10;
const int TL = 9;

int main(int argc, char *argv[]) {
    set<pair<int,int>> seen;
    array<pair<int,int>, SZ> rope;
    rope.fill({15, 11});

    char dir;
    int dist;
    while (cin >> dir >> dist) {
        int dy = dir == 'L' ? -1 : dir == 'R' ? 1 : 0,
            dx = dir == 'U' ? -1 : dir == 'D' ? 1 : 0;
        while (dist--) {
            rope[0].first += dx;
            rope[0].second += dy;
            for (int i = 1; i < SZ; ++i) {
                auto& [px, py] = rope[i-1];
                auto& [x, y] = rope[i];
                if (abs(px - x) + abs(py - y) > 2) {
                    if (abs(px - x) == 1) x = px;
                    else if (abs(py - y) == 1) y = py;
                }
                if (abs(px - x) > 1)
                    x = (px + x) / 2;
                if (abs(py - y) > 1)
                    y = (py + y) / 2;
            }
            seen.insert(rope.back());
        }
    }
    cout << seen.size() << '\n';
    return 0;
}
