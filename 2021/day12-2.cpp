// -*- compile-command: "make d12" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    std::unordered_map<string,vector<string>> g;

    vector<string> parts;
    string line;
    while (getline(cin, line)) {
        split(line, parts, '-');
        string u = parts[0], v = parts[1];
        if (v != "start") g[u].push_back(v);
        if (u != "start") g[v].push_back(u);
    }

    queue<tuple<string,unordered_set<string>,bool>> q;
    q.push({ "start", { "start" }, false });

    int res = 0;
    while (!q.empty()) {
        auto [u, seen, twice] = q.front(); q.pop();
        if (u == "end") ++res;
        else {
            for (auto& v : g[u]) {
                if (v == "end") ++res;
                else {
                    if (!seen.count(v) || isupper(v[0])) {
                        std::unordered_set<string> nxt(seen);
                        nxt.insert(v);
                        q.push({ v, nxt, twice });
                    }
                    else if (twice) continue;
                    else q.push({ v, seen, true });
                }
            }
        }
    }

    cout << res << endl;
    return 0;
}
