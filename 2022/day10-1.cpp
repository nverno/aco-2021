// -*- compile-command: "make d10" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string cmd;
    int cycle = 0, X = 1, nxt = 20, res = 0;

    while (cin >> cmd) {
        int val = 0;
        if (cmd == "noop") ++cycle;
        else {
            cin >> val;
            cycle += 2;
        }

        if (cycle >= nxt) {
            res += nxt * X;
            nxt += 40;
        }
        X += val;
    }

    cout << res << '\n';
    
    return 0;
}
