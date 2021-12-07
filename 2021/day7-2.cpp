// -*- compile-command: "make d7" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    vector<int> arr;
    split(line, arr, ',');

    int mx = INT_MIN, mn = INT_MAX;
    for (auto& x : arr) {
        mx = max(x, mx);
        mn = min(x, mn);
    }

    int res = INT_MAX;
    for (int pos = mn; pos <= mx; ++pos) {
        int cur = 0;
        for (auto& x : arr) {
            int d = abs(x - pos);
            cur += d*(d+1) / 2;
        }
        res = min(res, cur);
    }
    cout << res << endl;
    return 0;
}
