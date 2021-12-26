// -*- compile-command: "make d21" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    int p1 = line.back() - '0';
    getline(cin, line);
    int p2 = line.back() - '0';

    array<int,2> scores = {0, 0}, loc = {p1-1, p2-1};
    int p = 0, n = 0, cur = 1;
    while (scores[0] < 1000 && scores[1] < 1000) {
        n += 3;
        int moves = 3*cur + 3;
        cur += 3;
        loc[p] = (loc[p] + moves) % 10;
        scores[p] += loc[p] + 1;
        p ^= 1;
    }
    cout << n * min(scores[0], scores[1]) << endl;
    return 0;
}
