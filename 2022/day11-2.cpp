// -*- compile-command: "make d11" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

int mod = 1;

struct monkey {
    int id, next[2], div;
    ll cnt = 0;
    vector<ll> items;
    vector<string> op;
    ll do_op(ll old) {
        ll a = op[0] == "old" ? old : stoi(op[0]),
           b = op[2] == "old" ? old : stoi(op[2]);
        return op[1] == "+" ? a + b : a * b;
    }
    vector<pair<int,ll>> throw_items() {
        const int n = items.size();
        vector<pair<int,ll>> res;
        for (int i = 0; i < n; ++i) {
            ++cnt;
            ll v = do_op(items[i]) % mod;
            res.push_back({next[v % div != 0], v});
        }
        items.clear();
        return res;
    }
};
ostream& operator<<(ostream& os, const monkey& m) {
    const int n = m.items.size();
    os << m.id << " cnt=" << m.cnt << ": items=[";
    for (int i = 0; i < n; ++i) 
        os << m.items[i] << (i < n-1 ? "," : "");
    os << "] op=" << m.op[0] << " " << m.op[1] << " " << m.op[2]
       << ", div=" << m.div << ", next=[" << m.next[0] << ", " << m.next[1] << "]";
    return os;
}

int read_num() {
    string line;
    getline(cin, line);
    int res = 0;
    for (int i = 0; i < (int)line.size(); ++i) 
        if (isdigit(line[i])) 
            res = 10*res + (line[i] - '0');
    return res;
}

int main(int argc, char *argv[]) {
    vector<monkey> monks;
    string s;
    int id;
    while (scanf("Monkey %d:", &id) != -1) {
        monkey m;
        m.id = id;
        string line;
        cin >> s >> s;
        getline(cin, line);
        vector<int> items;
        split(line, items, ", ");
        for (auto& x : items) 
            m.items.push_back(x);
        getline(cin, line);
        vector<string> parts;
        split(line, parts);
        m.op = vector<string>(parts.end()-3, parts.end());
        m.div = read_num();
        mod *= m.div;
        m.next[0] = read_num();
        m.next[1] = read_num();
        monks.push_back(m);
        getline(cin, line);
    }

    for (int round = 1; round <= 10000; ++round) 
        for (auto& m : monks) 
            for (auto& [nxt, val] : m.throw_items()) 
                monks[nxt].items.push_back(val);

    sort(begin(monks), end(monks), [&](const auto& a, const auto& b) {
        return a.cnt > b.cnt;
    });
    cout << monks[0].cnt * monks[1].cnt << '\n';

    return 0;
}
