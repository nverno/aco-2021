// -*- compile-command: "make d25" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

ll to_dec(string snafu) {
    int n = snafu.size();
    ll mul = 1, res = 0;
    for (int i = n-1; i >= 0; --i) {
        if (isdigit(snafu[i]))
            res += (snafu[i]-'0') * mul;
        else if (snafu[i] == '-')
            res -= mul;
        else if (snafu[i] == '=')
            res -= 2LL*mul;
        else assert(0);
        mul *= 5LL;
    }
    return res;
}

string to_snafu(ll num) {
    ll mul = 1;
    while (2*mul < num) mul *= 5;
    string res;
    while (mul) {
        ll v = abs(num);
        if (v <= mul/2) {
            res += '0';
        } else {
            ll d = abs(mul - v);
            if (d <= mul/2) {
                res += (num < 0 ? '-' : '1');
                num = num < 0 ? num + mul : num - mul;
            } else {
                res += (num < 0 ? '=' : '2');
                num = num < 0 ? num + 2*mul : num - 2*mul;
            }
        }
        mul /= 5;
    }
    return res;
}

int main(int argc, char *argv[]) {
    string line;
    ll acc = 0;
    while (getline(cin, line)) 
        acc += to_dec(line);
    string res = to_snafu(acc);
    assert(acc == to_dec(res));
    cout << res << '\n';
    return 0;
}

