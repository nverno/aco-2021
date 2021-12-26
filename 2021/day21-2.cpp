// -*- compile-command: "make d21" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

pair<int,int> read() {
    string line;
    getline(cin, line);
    int p1 = line.back() - '0';
    getline(cin, line);
    int p2 = line.back() - '0';
    return {p1, p2};
}

const int win = 21;
using state = tuple<int,int,int,int>;
map<state,pair<ll,ll>> memo;
pair<ll,ll> dp(state cur, vector<int>& rolls) {
    if (memo.count(cur)) return memo[cur];
    auto [p1, p2, s1, s2] = cur;
    ll w1 = 0, w2 = 0;
    for (auto& r : rolls) {
        int np1 = ((p1 + r - 1) % 10) + 1,
            ns1 = s1 + np1;
        if (ns1 >= win) w1++;
        else {
            auto [nw1, nw2] = dp({ p2, np1, s2, ns1 }, rolls);
            w1 += nw2;
            w2 += nw1;
        }
    }
    return memo[cur] = {w1, w2};
}
    
int main(int argc, char *argv[]) {
    auto [p1, p2] = read();

    vector<int> rolls;
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 3; ++j)
            for (int k = 1; k <= 3; ++k)
                rolls.push_back(i+j+k);

    auto [w1, w2] = dp({p1, p2, 0, 0}, rolls);
    cout << w1 << ", " << w2 << endl;
    return 0;
}
