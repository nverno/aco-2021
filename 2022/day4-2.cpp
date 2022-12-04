// -*- compile-command: "make d4" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    int res = 0;
    string line;
    vector<string> arr;
    while (getline(cin, line)) {
        vector<int> rs(4);
        int j = 0;
        for (int i = 0; i < (int)line.size(); ++i) {
            if (line[i] == '-' || line[i] == ',') ++j;
            else rs[j] = 10 * rs[j] + (line[i] - '0');
        }
        if (rs[0] > rs[2] || (rs[0] == rs[2] && rs[1] < rs[3])) {
            swap(rs[0], rs[2]);
            swap(rs[1], rs[3]);
        }
        if (rs[1] >= rs[2]) ++res;
    }
    cout << res << '\n';
    return 0;
}
