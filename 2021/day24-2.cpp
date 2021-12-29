// -*- compile-command: "make d24" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    vector<tuple<int,int,int>> constraint;
    stack<pair<int,int>> st;
    string line;
    int idx = 0;
    while (getline(cin, line)) {
        size_t pos;
        if ((pos = line.find("inp w")) != string::npos) ++idx;
        else if ((pos = line.find("div z")) != string::npos) {
            int typ = stoi(line.substr(6));
            if (typ == 1) {
                for (int i = 0; i <= 10; ++i) getline(cin, line);
                assert(line.substr(0, 5) == "add y");
                st.push({ idx, stoi(line.substr(5)) });
            } else if (typ == 26) {
                getline(cin, line);
                assert(line.substr(0, 5) == "add x");
                int x = stoi(line.substr(5));
                auto [i, v] = st.top(); st.pop();
                constraint.push_back({ idx-1, i-1, x + v });
            } else assert(false);
        }
    }
    assert(idx == 14 && constraint.size() == 7);
    // cout << "read " << idx << " blocks" << endl;
    // cout << "constraints: ";
    // for (auto& [i, j, d] : constraint) {
    //     cout << i << ", " << j << ", " << d << endl;
    // }
    
    string res(14, '1');
    for (auto& [i, j, d] : constraint) {
        if (d > 0) res[i] = '0' + (1 + d);
        else res[j] = '0' + (1 - d);
    }
    cout << res << endl;
    return 0;
}
