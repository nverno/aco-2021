// -*- compile-command: "make d19" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int MINUTES = 32;

// 1:4 robots, 5:8 minerals
using state = array<int,8>;

int bfs(vector<int>& costs) {
    int o1 = costs[1],
        o2 = costs[2],
        o3 = costs[3], c3 = costs[4],
        o4 = costs[5], ob4 = costs[6];
    int mx1 = max({o1, o2, o3, o4});

    state init = {1, 0, 0, 0, 0, 0, 0, 0};
    set<state> seen;
    queue<state> q;
    q.push(init);

    int res = 0, t = MINUTES;
    while (t-- >= 0 && !q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto st = q.front(); q.pop();
            seen.insert(st);

            auto [r1, r2, r3, r4, ore, clay, obs, geo] = st;
            res = max(res, geo);
            if (t > 0) {
                ore = min(ore, t*mx1 - r1*(t-1));
                clay = min(clay, t*c3 - r2*(t-1));
                obs = min(obs, t*ob4 - r3*(t-1));
            }
            state ns = {r1, r2, r3, r4, ore+r1, clay+r2, obs+r3, geo+r4};
            if (!seen.count(ns)) seen.insert(ns), q.push(ns);

            if (r1 < mx1 && ore >= o1) {
                state s1 = {r1+1, r2, r3, r4, ore+r1-o1, clay+r2, obs+r3, geo+r4};
                if (!seen.count(s1)) seen.insert(s1), q.push(s1);
            }
            if (r2 < c3 && ore >= o2) {
                state s2 = {r1, r2+1, r3, r4, ore+r1-o2, clay+r2, obs+r3, geo+r4};
                if (!seen.count(s2)) seen.insert(s2), q.push(s2);
            }
            if (r3 < ob4 && ore >= o3 && clay >= c3) {
                state s3 = {r1, r2, r3+1, r4, ore+r1-o3, clay+r2-c3, obs+r3, geo+r4};
                if (!seen.count(s3)) seen.insert(s3), q.push(s3);
            }
            if (ore >= o4 && obs >= ob4) {
                state s4 = {r1, r2, r3, r4+1, ore+r1-o4, clay+r2, obs+r3-ob4, geo+r4};
                if (!seen.count(s4)) seen.insert(s4), q.push(s4);
            }
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    string line;
    int res = 1;
    while (getline(cin, line)) {
        vector<int> costs = read_ints(line);
        if (costs[0] > 3) break;
        int best = bfs(costs);
        // cout << costs[0] << ": " << best << '\n';
        res *= best;
    }
    cout << res << '\n';
    return 0;
}
