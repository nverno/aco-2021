// -*- compile-command: "make d2" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    char a, b;
    int score = 0;
    while (cin >> a >> b) {
        int x = a - 'A', y = b - 'X';
        score += y + 1;
        if (x == y) score += 3;
        else if (y == (x+1)%3) score += 6;
    }
    cout << score << '\n';
    return 0;
}
