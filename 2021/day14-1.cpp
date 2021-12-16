// -*- compile-command: "make d14" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
#include "../lib/trie.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    Trie<string> *t = new Trie<string>();
    vector<string> parts;
    string line, seq;
    getline(cin, seq);
    while (getline(cin, line)) {
        split(line, parts, "->");
        if (parts.size())
            t->add(parts[0], parts[1]);
    }

    for (int step = 1; step <= 10; ++step) {
        string res;
        for (size_t i = 0; i < seq.size(); ++i) {
            res += seq[i];
            auto node = t->lookup(seq.substr(i, 2));
            if (node) res += node->val;
        }
        // cout << "After step " << step << ": " << res << endl;
        swap(res, seq);
    }

    vector<int> cnt(26);
    for (auto& c : seq) cnt[c-'A']++;
    int mx = INT_MIN, mn = INT_MAX;
    for (auto& x : cnt) {
        if (x == 0) continue;
        mx = max(mx, x);
        mn = min(mn, x);
    }
    cout << mx - mn << endl;
    return 0;
}
