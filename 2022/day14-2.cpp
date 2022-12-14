// -*- compile-command: "make d14" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int maxN = 700;
const int shiftX = 200;
const int startX = 300;
array<int,2> ylim = {INT_MAX, 0}, xlim = {INT_MAX, 0};

void update_lims(array<int,2>& p) {
    ylim[0] = min(ylim[0], p[1]);
    ylim[1] = max(ylim[1], p[1]);
    xlim[0] = min(xlim[0], p[0]);
    xlim[1] = max(xlim[1], p[0]);
}

vector<array<int,2>> to_points(string line) {
    vector<string> parts;
    split(line, parts, " -> ");
    vector<array<int,2>> res;
    for (auto& p : parts) {
        array<int,2> point = {0, 0};
        int j = 0;
        for (char const &c: p) {
            if (c == ',') ++j;
            else point[j] = 10*point[j] + (c-'0');
        }
        point[0] -= shiftX;
        res.push_back(point);
        update_lims(point);
    }
    return res;
}

int sign(int v) {
    return (0 < v) - (v < 0);
}

int main(int argc, char *argv[]) {
    vector<vector<char>> g(maxN, vector<char>(maxN, '.'));
    string line;
    int idx = 0;
    while (getline(cin, line)) {
        auto ps = to_points(line);
        int n = ps.size();
        for (int i = 1; i < n; ++i) {
            auto [x, y] = ps[i-1];
            auto [ex, ey] = ps[i];
            int dx = sign(ex - x),
                dy = sign(ey - y);
            while (!(x == ex && y == ey)) {
                g[y][x] = '#';
                x += dx;
                y += dy;
            }
            g[y][x] = '#';
        }
        ++idx;
    }
    // add floor at 2 + highest y-coord
    for (int j = 0; j < maxN; ++j) 
        g[ylim[1]+2][j] = '#';

    int res = 0;
    bool done = false;
    while (!done) {
        array<int,2> p = {0, startX};
        while (true) {
            auto& [y, x] = p;
            if (y+1 >= maxN || g[y][x] == 'o') {
                done = true;
                break;
            }
            if (g[y+1][x] == '.') ++y;
            else if (x > 0 && g[y+1][x-1] == '.') ++y, --x;
            else if (x < maxN-1 && g[y+1][x+1] == '.') ++y, ++x;
            else {
                g[y][x] = 'o';
                ++res;
                break;
            }
        }
    }

    // cout << endl;
    // cout << "ylim: " << ylim[0] << ":" << ylim[1] << '\n';
    // for (int i = 0; i < 220; ++i) {
    //     for (int j = startX; j < startX + 200; ++j) {
    //         cout << g[i][j];
    //     }
    //     cout << endl;
    // }

    cout << res << '\n';
    return 0;
}
