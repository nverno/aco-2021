// -*- compile-command: "make d5" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

bool nice(string& s) {
    std::unordered_set<string> pairs;
    int btw = 0, cnt = 0;
    bool skipped = false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (i < s.size()-1 && pairs.count(s.substr(i, 2)))
            ++cnt;
        if (s.substr(i,2) == s.substr(i+1,2)) {
            if (skipped) {
                pairs.insert(s.substr(i, 2));
                skipped = false;
            } else skipped = true;
        } else {
            skipped = false;
            pairs.insert(s.substr(i, 2));
        }
        if (i < s.size()-2 && s[i] == s[i+2])
            ++btw;
    }
    return btw > 0 && cnt > 0;
}

int main(int argc, char *argv[]) {
    vs = std::unordered_set<char>(vowels.begin(), vowels.end());
    string line;
    int res = 0;
    while (getline(cin, line)) {
        if (nice(line)) ++res;
    }
    cout << res << endl;
    return 0;
}
