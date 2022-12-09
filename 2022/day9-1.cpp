// -*- compile-command: "make d9" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    set<pair<int,int>> seen;
    pair<int,int> hd = {0, 0}, tl = hd;
    char dir;
    int dist;
    while (cin >> dir >> dist) {
        int dy = dir == 'L' ? -1 : dir == 'R' ? 1 : 0,
            dx = dir == 'U' ? -1 : dir == 'D' ? 1 : 0;
        while (dist--) {
            hd.first += dx;
            hd.second += dy;
            if (abs(hd.first - tl.first) > 1) {
                tl.first += dx;
                tl.second = hd.second;
            }
            else if (abs(hd.second - tl.second) > 1) {
                tl.second += dy;
                tl.first = hd.first;
            }
            seen.insert(tl);
        }
    }
    cout << seen.size() << '\n';
    return 0;
}
