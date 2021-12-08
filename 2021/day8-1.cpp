// -*- compile-command: "make d8" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    vector<string> parts, outs;
    int res = 0;
    string line;
    while (getline(cin, line)) {
        split(line, parts, '|');
        split(parts[1], outs);
        std::unordered_set<char> chrs;
        for (auto& s : outs) {
            std::unordered_set<char> ch(s.begin(), s.end());
            int sz = ch.size();
            if (sz == 2 || sz == 4 || sz == 3 || sz == 7)
                ++res;
        }
    }
    cout << res << endl;
    return 0;
}
