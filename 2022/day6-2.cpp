// -*- compile-command: "make d6" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int SZ = 14;

int main(int argc, char *argv[]) {
    string txt;
    cin >> txt;
    vector<int> cnt(26);
    int cur = 0, res = -1;
    for (int i = 0; i < (int)txt.size(); ++i) {
        if (++cnt[txt[i]-'a'] == 1) ++cur;
        if (i >= SZ && --cnt[txt[i-SZ]-'a'] == 0) --cur;
        if (cur == SZ) {
            res = i + 1;
            break;
        }
    }
    cout << res << '\n';
    return 0;
}
