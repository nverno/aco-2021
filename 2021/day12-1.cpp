// -*- compile-command: "make d12" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    unordered_map<string,vector<string>> g;
    vector<string> parts;
    string line;
    while (getline(cin, line)) {
        split(line, parts, '-');
        g[parts[0]].push_back(parts[1]);
        g[parts[1]].push_back(parts[0]);
    }

    int res = 0;
    queue<pair<string,unorderd_set<string>>> q;
    q.push({"start", { "start" }});

    while (!q.empty()) {
        auto u = q.front(); q.pop();
        if (u == "end") ++res;
        else {
            for (auto& v : g[u]) {
                if (!seen.count(u+v) || isupper(v[0])) {
                    q.push(v);
                    seen.insert(v);
                }
            }
        }
    }

    cout << res << endl;
    return 0;
}
