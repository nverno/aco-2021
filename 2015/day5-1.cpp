// -*- compile-command: "make d5" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

string vowels = "aeiou";
std::unordered_set<char> vs;
std::unordered_set<string> bad = {"ab","cd","pq","xy"};

bool nice(string& s) {
    bool two = false;
    int cnt = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (bad.count(s.substr(i, 2)))
            return false;
        if (vs.count(s[i]))
            ++cnt;
        if (i < s.size()-1 && s[i] == s[i+1])
            two = true;
    }
    return two && cnt > 2;
}

int main(int argc, char *argv[]) {
    vs = std::unordered_set<char>(vowels.begin(), vowels.end());
    string line;
    int res = 0;
    while (getline(cin, line)) {
        if (nice(line)) ++res;
    }
    cout << res << endl;
    return 0;
}
