// -*- compile-command: "make d10" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    unordered_map<char,char> m = {
        {'{','}'}, {'[',']'}, {'(',')'}, {'<','>'},
    };
    unordered_map<char,int> points = {
        {'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}
    };

    vector<long> scores;
    string line;
    while (getline(cin, line)) {
        bool skip = false;
        stack<char> st;
        for (size_t i = 0; !skip && i < line.size(); ++i) {
            char c = line[i];
            if (m.count(c)) st.push(c);
            else {
                if (st.empty() || m[st.top()] != c) {
                    skip = true;
                } else st.pop();
            }
        }
        if (!skip) {
            long v = 0;
            while (!st.empty()) {
                v *= 5;
                v += points[st.top()];
                st.pop();
            }
            scores.push_back(v);
        }
    }
    sort(scores.begin(), scores.end());
    cout << scores[scores.size()/2] << endl;
    return 0;
}
