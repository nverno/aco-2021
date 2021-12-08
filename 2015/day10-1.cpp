// -*- compile-command: "make d10" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string s = "3113322113";
    for (int i = 0; i < 40; ++i) {
        string nxt;
        int cnt = 1;
        char c = s[0];
        for (size_t j = 1; j < s.size(); ++j) {
            if (s[j] == c)
                ++cnt;
            else {
                nxt += to_string(cnt) + c;
                c = s[j];
                cnt = 1;
            }
        }
        nxt += to_string(cnt) + c;
        swap(s, nxt);
    }
    cout << s.size() << endl;
    return 0;
}
