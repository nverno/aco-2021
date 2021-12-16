// -*- compile-command: "make d14" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

#define ll long long

int main(int argc, char *argv[]) {
    std::unordered_map<string,pair<string,string>> m;
    vector<string> parts;
    string line, seq;
    getline(cin, seq);
    while (getline(cin, line)) {
        split(line, parts, "->");
        if (parts.size()) {
            string from = parts[0], to = parts[1];
            m[from] = { from[0]+to, to+from[1] };
        }
    }

    vector<ll> cnt(26);
    for (size_t i = 0; i < seq.size(); ++i) cnt[seq[i]-'A']++;

    std::unordered_map<string,ll> cur, nxt;
    for (size_t i = 0; i < seq.size()-1; ++i)
        cur[seq.substr(i, 2)]++;

    for (int step = 1; step <= 40; ++step) {
        nxt.clear();
        for (auto& [k, v] : cur) {
            auto [a, b] = m[k];
            cnt[a[1]-'A'] += v;
            nxt[a] += v;
            nxt[b] += v;
        }
        swap(cur, nxt);
    }
    
    ll mx = LLONG_MIN, mn = LLONG_MAX;
    for (auto& x : cnt) {
        if (x == 0) continue;
        mx = max(mx, x);
        mn = min(mn, x);
    }
    cout << mx - mn << endl;
    return 0;
}
