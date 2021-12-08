// -*- compile-command: "make d8" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

bool contains(string a, string b) {
    if (a.size() < b.size()) return false;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) ++i, ++j;
        else if (a[i] < b[j]) ++i;
        else return false;
    }
    return j == b.size();
}

string getDiff(string a, string b) {
    string res;
    size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] == b[j]) ++i, ++j;
        else if (a[i] < b[j]) res += a[i++];
        else res += b[j++];
    }
    return res + a.substr(i) + b.substr(j);
}

unordered_map<string,int> mapStrings(vector<string>& arr) {
    vector<string> nums(10), fives, sixes;
    for (auto& s : arr) {
        std::sort(s.begin(), s.end());
        if (s.size() == 2) nums[1] = s;
        else if (s.size() == 3) nums[7] = s;
        else if (s.size() == 4) nums[4] = s;
        else if (s.size() == 7) nums[8] = s;
        else if (s.size() == 5) fives.push_back(s);
        else if (s.size() == 6) sixes.push_back(s);
        else assert(false);
    }
    for (auto& s : sixes) {
        if (contains(s, nums[4])) nums[9] = s;
        else if (contains(s, nums[7])) nums[0] = s;
        else nums[6] = s;
    }
    for (auto& s : fives) {
        if (contains(s, nums[1])) nums[3] = s;
        else if (contains(s, getDiff(nums[4], nums[7]))) nums[5] = s;
        else nums[2] = s;
    }
    std::unordered_map<string,int> res;
    for (size_t i = 0; i < nums.size(); ++i)
        if (!empty(nums[i])) res[nums[i]] = i;
    return res;
}

int main(int argc, char *argv[]) {
    vector<string> parts, ins, outs;
    int res = 0;
    string line;
    while (getline(cin, line)) {
        split(line, parts, '|');
        split(parts[1], outs);
        split(parts[0], ins);
        unordered_map<string,int> m = mapStrings(ins);
        int num = 0;
        for (auto& v : outs) {
            std::sort(v.begin(), v.end());
            num *= 10;
            num += m[v];
        }
        // for (auto& [s, n] : m) {
        //     cout << s << ": " << n << endl;
        // }
        // std::copy(outs.begin(), outs.end(), std::ostream_iterator<decltype(outs[0])>(std::cout, " "));
        // cout << ": " << num << endl;
        res += num;
    }
    cout << res << endl;
    return 0;
}
