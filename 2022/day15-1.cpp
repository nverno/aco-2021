// -*- compile-command: "make d15" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int mdist(vector<int>& cs) {
    return abs(cs[0]-cs[2]) + abs(cs[1]-cs[3]);
}

const int ROW = 2000000; //10;

int main(int argc, char *argv[]) {
    string line;
    set<int> hits;

    while (getline(cin, line)) {
        vector<int> coords = read_ints(line);
        int x = coords[0], y = coords[1],
            d = mdist(coords),
         over = y > ROW ? ROW - (y - d) : y + d - ROW;
        if (over <= 0) continue;

        for (int i = x-over; i < x+over; ++i) 
            hits.insert(i);
    }

    cout << hits.size() << '\n';
    return 0;
}
