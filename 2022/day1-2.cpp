// -*- compile-command: "make d1" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    vector<int> v;
    string line;
    int cur = 0;
    while (getline(cin, line)) {
        if (line.empty()) v.push_back(cur), cur = 0;
        else cur += stoi(line);
    }
    sort(v.rbegin(), v.rend());
    cout << v[0] + v[1] + v[2] << '\n';
    return 0;
}
