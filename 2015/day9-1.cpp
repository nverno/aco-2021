// -*- compile-command: "make d9" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    unordered_map<int,unordered_map<int,int>> g;
    unordered_map<string,int> idx;
    int i = 0;
    vector<string> parts;
    string line;
    while (getline(cin, line)) {
        split(line, parts);
        int d = stoi(parts.back());
        string u = parts[0], v = parts[2];
        if (!idx.count(u)) idx[u] = i++;
        if (!idx.count(v)) idx[v] = i++;
        g[idx[u]][idx[v]] = g[idx[v]][idx[u]] = d;
    }

    const int n = g.size();
    int res = INT_MAX;
    for (int start = 0; start < n; ++start) {
        queue<tuple<int,int,int>> q;
        q.push({ 0, start, (1 << start) });  // distance, last, seen
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [d, prev, seen] = q.front(); q.pop();
                if (__builtin_popcount(seen) == n) {
                    res = min(res, d);
                } else {
                    for (auto& [c, dx] : g[prev]) {
                        if ((1 << c) & seen) continue;
                        seen |= (1 << c);
                        q.push({ d + dx, c, seen });
                        seen ^= (1 << c);
                    }
                }
            }
        }
    }

    cout << res << endl;
    return 0;
}
