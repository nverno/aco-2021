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
        int num = 0;
        for (auto& v : outs) {
            num *= 10;
            std::sort(v.begin(), v.end());
            
            if (v.size() == 1 || v == "ab") num += 1;
            if (v == "abd") num += 7;
            if (v.size() == 4 || v == "abfe") num += 4;
            if (v == "abcdf") num += 3;
            if (v == "acdfg") num += 2;
            if (v == "bcdef") num += 5;
            if (v == "abcdeg") num += 0;
            if (v == "bcdefg") num += 6;
            if (v == "abcdef") num += 9;
            if (v == "abcdefg")num += 8;
        }
        cout << num << endl;
        res += num;
    }
    cout << res << endl;
    return 0;
}
