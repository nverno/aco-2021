// -*- compile-command: "make d2"; -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string line;
    int res = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<int> dim = split(line, 'x');
        int l = dim[0], w = dim[1], h = dim[2],
           s1 = l*w, s2 = w*h, s3 = h*l;
        res += 2*(l*w + w*h + h*l) + min({ s1, s2, s3 });
    }
    cout << res << endl;
    return 0;
}
