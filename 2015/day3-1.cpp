// -*- compile-command: "make d3" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    set<pair<int,int>> seen;
    int x = 0, y = 0;
    string line;
    getline(cin, line);
    for (char const &c: line) {
        seen.insert({x, y});
        if (c == '^') ++y;
        else if (c == 'v') --y;
        else if (c == '>') ++x;
        else if (c == '<') --x;
        seen.insert({x, y});
    }
    cout << seen.size() << endl;
    return 0;
}
