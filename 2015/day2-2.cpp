// -*- compile-command: "make d2" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string line;
    int res = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> dim = split(line, 'x');
        int l = dim[0], w = dim[1], h = dim[2];
        int a = min(l, w), b = min(h, max(l, w));
        res += 2*(a + b) + l*w*h;
    }
    cout << res << endl;
    return 0;
}
