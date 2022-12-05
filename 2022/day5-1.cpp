// -*- compile-command: "make d5" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int maxN = 9;

int main(int argc, char *argv[]) {
    vector<vector<char>> stacks(maxN);
    string line;
    bool done = false;
    while (!done && getline(cin, line)) {
        for (int i = 1; i < (int)line.size(); i += 4) {
            if (isdigit(line[i])) {
                done = true;
                break;
            }
            if (line[i] != ' ')
                stacks[i/4].push_back(line[i]);
        }
    }
    for (auto& st : stacks) 
        reverse(st.begin(), st.end());

    while (getline(cin, line)) {
        array<int,3> v{0};
        int n = line.size();
        for (int i = 0, j = 0; i < n; ++i) {
            if (isdigit(line[i])) {
                assert(j < 3);
                while (i < n && isdigit(line[i])) {
                    v[j] = 10*v[j] + (line[i] - '0');
                    ++i;
                }
                ++j;
            }
        }
        auto [cnt, a, b] = v;
        while (cnt--) {
            int x = stacks[a-1].back(); stacks[a-1].pop_back();
            stacks[b-1].push_back(x);
        }
    }
    for (auto& st : stacks) {
        if (!st.empty()) cout << st.back();
    }
    cout << '\n';
    return 0;
}
