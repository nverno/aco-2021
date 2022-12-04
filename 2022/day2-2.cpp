// -*- compile-command: "make d2" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

enum outcome {
    LOSE, TIE, WIN
};
int main(int argc, char *argv[]) {
    int score = 0;
    char a, b;
    while (cin >> a >> b) {
        int x = a - 'A', y = b - 'X';
        score++;
        if (y == TIE)
            score += 3 + x;
        else if (y == LOSE)
            score += (x + 2) % 3;
        else
            score += 6 + (x + 1) % 3;
    }
    cout << score << '\n';
    return 0;
}
