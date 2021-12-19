// -*- compile-command: "make d17" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

vector<int> xs, ys;
inline bool checkBounds(int x, int y) {
    return x >= xs[0] && x <= xs[1] && y >= ys[0] && y <= ys[1];
}

pair<bool,int> check(int dx, int dy) {
    int x = 0, y = 0, prev = 0;
    bool ok = false;
    while (x <= xs[1] && y >= ys[0]) {
        x += dx;
        y += dy;
        if (checkBounds(x, y)) {
            cout << "in bounds at (" << x << "," << y << ")\n";
            ok = true;
        }
        if (y == ys[0]) break;
        if (y > prev)
            prev = y;
        if (dx != 0)
            dx += (dx < 0 ? 1 : -1);
        dy -= 1;
    }
    return {ok, prev};
}

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    vector<string> parts;
    split(line, parts);
    string xx = parts[2].substr(2, parts[2].size()-3),
           yy = parts[3].substr(2);
    split(xx, xs, "..");
    split(yy, ys, "..");

    int res = 0;
    for (int x = -400; x <= 400; ++x) {
        for (int y = -400; y <= 400; ++y) {
            auto [ok, top] = check(x, y);
            if (ok) ++res;
                // res = max(res, top);
        }
    }
    cout << res << endl;
    return 0;
}
