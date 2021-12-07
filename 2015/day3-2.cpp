// -*- compile-command: "make d3" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    set<pair<int,int>> seen;
    int x = 0, y = 0, xx = 0, yy = 0, i = 0;
    string line;
    getline(cin, line);
    for (char const &c: line) {
        int idx = i % 2;
        idx ? seen.insert({x, y}) : seen.insert({xx, yy});
        if (c == '^') idx ? ++y : ++yy;
        else if (c == 'v') idx ? --y : --yy;
        else if (c == '>') idx ? ++x : ++xx;
        else if (c == '<') idx ? --x : --xx;
        idx ? seen.insert({x, y}) : seen.insert({xx, yy});
        ++i;
    }
    cout << seen.size() << endl;
    return 0;
}
