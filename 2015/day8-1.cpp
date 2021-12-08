// -*- compile-command: "make d8" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int countMem(string s) {
    int res = 0;
    size_t pos = 0;
    while ((pos = s.find("\\\\", pos)) != string::npos) {
        ++res;
        s.erase(pos, 2);
    }
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '\\') {
            if (s[i+1] == 'x')
                i += 3;
            else
                i++;
        }
        ++res;
    }
    return res - 2;
}

int main(int argc, char *argv[]) {
    vector<string> lines;
    int code = 0;
    string line;
    while (getline(cin, line)) {
        code += line.size();
        lines.push_back(line);
    }

    int mem = 0;
    for (auto& s : lines) {
        cout << s << ": " << countMem(s) << endl;
        mem += countMem(s);
    }

    cout << "code=" << code << ", mem=" << mem << endl;
    cout << code - mem << endl;
    return 0;
}
