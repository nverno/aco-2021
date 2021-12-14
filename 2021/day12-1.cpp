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
        g[u].push_back(v);
        g[v].push_back(u);
    }

    queue<pair<vector<string>,unordered_set<string>>> q;
    std::unordered_set<string> st;
    st.insert("start");
    q.push({{ "start" }, st });

    int res = 0;
    while (!q.empty()) {
        auto [p, seen] = q.front(); q.pop();
        string& u = p.back();
        if (u == "end") {
            ++res;
            continue;
        }
        for (auto& v : g[u]) {
            if (v == "end") ++res;
            else {
                if (!seen.count(v) || isupper(v[0])) {
                    std::unordered_set<string> nxt(seen);
                    vector<string> pp(p);
                    pp.push_back(v);
                    nxt.insert(v);
                    q.push({ pp, nxt });
                    
                }
            }
        }
    }

    cout << res << endl;

    return 0;
}
