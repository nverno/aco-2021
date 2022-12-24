// -*- compile-command: "make d21" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

map<string,ll> val;
map<string,char> op;
map<string,vector<string>> g;
map<string,ll> dp;

ll compute(string u) {
    if (dp.count(u)) return dp[u];
    if (!g.count(u)) return dp[u] = val[u];
    char o = op[u];
    ll a = compute(g[u][0]),
       b = compute(g[u][1]),
       v = o == '+' ? a + b : o == '-' ? a - b : o == '*' ? a * b : a / b;
    return dp[u] = v;
}

int main(int argc, char *argv[]) {
    string line;
    while (getline(cin, line)) {
        string u = line.substr(0, 4);
        if (isdigit(line[6])) {
            ll num = 0;
            for (int i = 6; i < (int)line.size(); ++i) {
                if (!isdigit(line[i])) break;
                num = 10*num + (line[i] - '0');
            }
            val[u] = num;
        } else {
            string a = line.substr(6, 4), b = line.substr(13, 4);
            char o = line[11];
            g[u].push_back(a);
            g[u].push_back(b);
            op[u] = o;
        }
    }
    cout << compute("root") << '\n';
    return 0;
}
