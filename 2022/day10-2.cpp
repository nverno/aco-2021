// -*- compile-command: "make d10" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int WIDTH = 40, HEIGHT = 6;

int main(int argc, char *argv[]) {
    string cmd;
    int cycle = 0, X = 1;
    vector<int> reg;
    while (cin >> cmd) {
        int val = 0;
        if (cmd == "addx") {
            cin >> val;
            reg.push_back(X);
            cycle += 2;
        }
        else cycle++;

        reg.push_back(X);
        X += val;
    }

    cout << '\n';
    for (int i = 0, idx = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j, ++idx) {
            if (abs(reg[idx] - j) <= 1) cout << '#';
            else cout << '.';
        }
        cout << '\n';
    }

    return 0;
}
