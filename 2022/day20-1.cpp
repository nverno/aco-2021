// -*- compile-command: "make d20" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

int main(int argc, char *argv[]) {
    list<int> nums;
    vector<list<int>::iterator> its;
    int num;
    while (cin >> num) {
        nums.push_back(num);
        its.push_back(prev(end(nums)));
    }

    const int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int v = *its[i] % n;
        if (v == 0) continue;
        auto it = its[i];
        if (v < 0) {
            while (v++) {
                if (it == begin(nums)) it = end(nums);
                --it;
            }
            if (it == begin(nums)) it = end(nums);
        } else {
            while (v-- >= 0) {
                ++it;
                if (it == end(nums)) it = begin(nums);
            }
        }
        if (it == its[i]) continue;
        nums.insert(it, *its[i]);
        nums.erase(its[i]);
    }
    
    vector<int> mixed(begin(nums), end(nums));
    int zi = find(begin(mixed), end(mixed), 0) - begin(mixed),
       res = 0;
    for (auto& x : {1000, 2000, 3000}) 
        res += mixed[(zi+x)%n];
    // cout << endl;
    // copy(mixed.begin(), mixed.end(), ostream_iterator<decltype(mixed[0])>(cout, " "));
    // cout << endl;

    cout << res << '\n';
    return 0;
}
