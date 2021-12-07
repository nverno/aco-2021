// -*- compile-command: "make d7" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

// O(nlog(n)) binary search
int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    vector<int> arr;
    split(line, arr, ',');

    auto score = [&](int mid) {
        int acc = 0;
        for (auto& x : arr) {
            int d = abs(x - mid);
            acc += d*(d+1)/2;
        }
        return acc;
    };

    int r = INT_MIN, l = INT_MAX;
    for (auto& x : arr) {
        r = max(x, r);
        l = min(x, l);
    }

    while (l < r) {
        int mid = (l + r + 1) / 2,
              v = score(mid),
             vr = (mid < arr.size() - 1) ? score(mid+1) : INT_MAX;
        if (vr < v) l = mid + 1;
        else r = mid;
    }
    cout << score(l) << endl;
    return 0;
}
