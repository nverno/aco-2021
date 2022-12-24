// -*- compile-command: "make d20" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

const ll key = 811589153;

int main(int argc, char *argv[]) {
    list<ll> nums;
    vector<list<ll>::iterator> its;
    ll num;
    while (cin >> num) {
        nums.push_back(key * num);
        its.push_back(prev(end(nums)));
    }

    const int n = nums.size();
    for (int round = 1; round <= 10; ++round) {
        for (int i = 0; i < n; ++i) {
            auto& it = its[i];
            ll x = *it, v = x % n;

            if (v < 0) {
                while (v++) 
                    it = it == begin(nums) ? end(nums) : prev(it);
            } else if (v > 0) {
                while (v-- >= 0) {
                    ++it;
                    if (it == end(nums)) it = begin(nums);
                }
            }
            // if (it == its[i]) continue;
            nums.insert(it, *its[i]);
            nums.erase(its[i]);
            its[i] = prev(it);
        }
    }    

    vector<int> mixed(begin(nums), end(nums));
    int zi = find(begin(mixed), end(mixed), 0) - begin(mixed);
    ll res = 0;
    for (auto& x : {1000, 2000, 3000}) 
        res += mixed[(zi+x)%n];
    cout << endl;
    copy(mixed.begin(), mixed.end(), ostream_iterator<decltype(mixed[0])>(cout, " "));
    cout << endl;

    cout << res << '\n';
    return 0;
}
