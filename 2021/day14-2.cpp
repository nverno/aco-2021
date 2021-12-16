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

    std::unordered_map<string,ll> cnt, tmp, res;
    for (int i = 0; i < seq.size()-1; ++i)
        cnt[s.substr(i, 2)]++;

    for (int step = 1; step <= 40; ++step) {
        tmp.clear();
        for (auto& [k, v] : cnt) {
            
        }
        for (size_t i = 0; i < seq.size(); ++i) {
            res += seq[i];
            auto node = t->lookup(seq.substr(i, 2));
            if (node) res += node->val;
        }
        // cout << "After step " << step << ": " << res << endl;
        swap(res, seq);
    }

    vector<ll> cnt(26);
    for (auto& c : seq) cnt[c-'A']++;
    ll mx = INT_MIN, mn = INT_MAX;
    for (auto& x : cnt) {
        if (x == 0) continue;
        mx = max(mx, x);
        mn = min(mn, x);
    }
    cout << mx - mn << endl;
    return 0;
}
