// -*- compile-command: "make d15" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

// const int maxN = 20, minN = 0;
const int maxN = 4e6, minN = 0;

ll tuning(int x, int y) {
    return (ll)x * (ll)4e6 + y;
}

int mdist(vector<int>& cs) {
    return abs(cs[0]-cs[2]) + abs(cs[1]-cs[3]);
}

struct sensor {
    int x, y, d;
    pair<bool,pair<int,int>> coverage(int row) {
        int over = y > row ? row - (y - d) : y + d - row;
        if (over <= 0) return {false, {0,0}};
        return {true, {x-over, x+over}};
    }
};

int check_coverage(vector<pair<int,int>>& cover) {
    sort(cover.begin(), cover.end()); //, [&](const auto& a, const auto& b) {
    int lo = cover[0].first,
        hi = cover[0].second;
    if (lo > minN) return lo-1;
    
    for (int i = 1; i < (int)cover.size(); ++i) {
        auto& c = cover[i];
        if (hi+1 < c.first) return hi+1;
        hi = max(hi, c.second);
    }
    return hi < maxN ? hi+1 : INT_MIN;
}

int main(int argc, char *argv[]) {
    string line;
    vector<sensor> sensors;

    while (getline(cin, line)) {
        vector<int> coords = read_ints(line);
        int x = coords[0], y = coords[1],
            d = mdist(coords);
        sensors.push_back(sensor{x, y, d});
    }

    int rx = -1, ry = -1;
    for (int row = 0; row <= maxN; ++row) {
        vector<pair<int,int>> cover;
        for (auto& s : sensors) {
            auto [ok, cov] = s.coverage(row);
            if (ok) cover.push_back(cov);
        }
        int x = check_coverage(cover);
        if (x != INT_MIN) {
            rx = x;
            ry = row;
            break;
        }
    }

    // 10621647166538
    cout << rx << ", " << ry << ": " << tuning(rx, ry) << '\n';
    return 0;
}
