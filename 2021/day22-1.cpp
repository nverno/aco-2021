// -*- compile-command: "make d22" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

struct Seg {
    pair<int,int> x, y, z;
    Seg() {}
    Seg(string s, int offset = 50) {
        vector<string> parts;
        split(s, parts, ',');
        for (int i = 0; i < parts.size(); ++i) {
            auto &p = parts[i];
            size_t pos = 2;
            while (p[pos] == '-' || isdigit(p[pos])) ++pos;
            int a = stoi(p.substr(2, pos-2)) + offset,
                b = stoi(p.substr(pos+2)) + offset;
            if (i == 0) x = {a, b};
            else if (i == 1) y = {a, b};
            else z = {a, b};
        }
    }
};

using grid3d = vector<vector<vector<int>>>;

int main(int argc, char *argv[]) {
    int mx = 51;
    grid3d mat(2*mx, vector<vector<int>>(2*mx, vector<int>(2*mx)));
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        size_t pos = line.find(" ");
        Seg seg(line.substr(pos+1), 50);
        int v = line.substr(0, pos) == "on" ? 1 : 0;
        auto [xi, xj] = seg.x;
        auto [yi, yj] = seg.y;
        auto [zi, zj] = seg.z;
        for (int i = max(0, xi); i <= min(100, xj); ++i) {
            for (int j = max(0, yi); j <= min(100, yj); ++j) {
                for (int k = max(0, zi); k <= min(100, zj); ++k) {
                    mat[i][j][k] = v;
                }
            }
        }
    }
    int res = 0;
    for (auto& r : mat) {
        for (auto& y : r) {
            for (auto& e : y) {
                res += e;
            }
        }
    }
    cout << res << endl;
    return 0;
}
