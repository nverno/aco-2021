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

    auto [lp, rp] = minmax_element(arr.begin(), arr.end());
    int l = *lp, r = *rp;
    while (l < r) {
        int mid = (l + r + 1) / 2,
              v = score(mid),
             vr = (mid < (int)arr.size() - 1) ? score(mid+1) : INT_MAX;
        if (vr < v) l = mid + 1;
        else r = mid;
    }
    cout << score(l) << endl;
    return 0;
}
