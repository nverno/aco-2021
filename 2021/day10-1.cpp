// -*- compile-command: "make d10" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    unordered_map<char,char> m = {
        {'{','}'}, {'[',']'}, {'(',')'}, {'<','>'},
    };
    unordered_map<char,int> points = {
        {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}
    };

    int res = 0;
    string line;
    while (getline(cin, line)) {
        stack<char> st;
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (m.count(c)) st.push(c);
            else {
                if (st.empty() || m[st.top()] != c) {
                    res += points[c];
                    break;
                } else st.pop();
            }
        }
    }
    cout << res << endl;
    return 0;
}
