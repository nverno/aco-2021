// -*- compile-command: "make d8" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int countEncoded(string s) {
    int res = 0;
    size_t pos = 0;
    while ((pos = s.find("\\\\", pos)) != string::npos) {
        res += 4;
        s.erase(pos, 2);
    }
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '\\') {
            if (s[i+1] == 'x')
                ++res;
            else
                res += 2;
        }
        ++res;
    }
    return res + 4;
}

int main(int argc, char *argv[]) {
    vector<string> lines;
    int code = 0;
    string line;
    while (getline(cin, line)) {
        code += line.size();
        lines.push_back(line);
    }

    int enc = 0;
    for (auto& s : lines) {
        cout << s << ": " << countEncoded(s) << endl;
        enc += countEncoded(s);
    }

    cout << "code=" << code << ", enc=" << enc << endl;
    cout << enc - code << endl;
    return 0;
}
