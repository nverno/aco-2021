// -*- compile-command: "make d3" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    int res = 0;
    string A, B, C;
    while (cin >> A >> B >> C) {
        vector<int> ca(256), cb(256);
        for (char const &c: A) ca[c]++;
        for (char const &c: B) cb[c]++;
        for (char const &c: C) {
            if (ca[c] && cb[c]) {
                res += isupper(c) ? (c - 'A') + 27 : (c - 'a') + 1;
                break;
            }
        }
    }
    cout << res << '\n';
    return 0;
}
