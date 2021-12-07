// -*- compile-command: "make d7" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    vector<int> arr;
    split(line, arr, ',');

    std::sort(arr.begin(), arr.end());
    int mid = arr[arr.size() / 2];
    int res = 0;
    for (auto& x : arr)
        res += abs(x - mid);
    cout << res << endl;
    return 0;
}
