// -*- compile-command: "make d3" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    int res = 0;
    string line;
    while (getline(cin, line)) {
        int n = line.size();
        vector<int> cnt(256);
        for (int i = 0; i < n/2; ++i) cnt[line[i]]++;
        for (int i = n/2; i < n; ++i) {
            if (cnt[line[i]]) {
                res += isupper(line[i]) ? (line[i] - 'A') + 27 : (line[i] - 'a') + 1;
                break;
            }
        }
    }
    cout << res << '\n';
    return 0;
}
