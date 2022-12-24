// -*- compile-command: "make d21" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

const ll X = LLONG_MIN;
const string ME = "humn";
const string ROOT = "root";

map<string,ll> val;
map<string,char> op;
map<string,vector<string>> g;
map<string,ll> dp;

ll compute(string u) {
    if (dp.count(u)) return dp[u];
    if (!g.count(u)) return dp[u] = val[u];
    char o = op[u];
    ll a = compute(g[u][0]),
       b = compute(g[u][1]);
    if (a == X || b == X) return dp[u] = (u == ROOT ? (a == X ? b : a) : X);
    return dp[u] = o == '+' ? a + b : o == '-' ? a - b : o == '*' ? a * b : a / b;
}

void solve(string u, ll target) {
    if (u == ME) val[ME] = target; 
    if (val.count(u)) return;

    string a = g[u][0], b = g[u][1];
    ll av = dp[a], bv = dp[b];
    if (!(av == X || bv == X)) return;

    cout << "solve: " << u << ": "
         << (av == X ? "X" : to_string(av)) << " " << op[u] << " " << (bv == X ? "X" : to_string(bv))
         << " = " << target << '\n';
    
    if (u != ROOT) {
        switch (op[u]) {
            case '/': target = av == X ? target * bv : av / target; break;
            case '*': target /= (av == X ? bv : av); break;
            case '-': target = (av == X ? target+bv : av-target); break;
            case '+': target -= (av == X ? bv : av); break;
            default: assert(0);
        }
    }
    solve(av == X ? a : b, target);
}

int main(int argc, char *argv[]) {
    string line;
    while (getline(cin, line)) {
        string u = line.substr(0, 4);
        if (u == ME) {
            val[u] = X;
            continue;
        }
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

    ll target = compute(ROOT);
    solve(ROOT, target);
    cout << val[ME] << '\n';
    return 0;
}
