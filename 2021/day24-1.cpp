// -*- compile-command: "make d24" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

// inp w
// mul x 0
// add x z
// mod x 26
// div z 1
// add x 13  x = (z % 26) + 13
// eql x w   
// eql x 0   x != w => x = 1 since 1 <= w <= 9
// mul y 0
// add y 25
// mul y x   
// add y 1   y = 25 * (x != w) + 1 => y = 26
// mul z y   z = 26 * z
// mul y 0
// add y w
// add y 10
// mul y x   y = (w + 10)
// add z y   z = 26*z + w + 10
// => z = 26*z + w + 10, y = w+10, x = 1

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
    
    string res(14, '9');
    for (auto& [i, j, d] : constraint) {
        if (d > 0) res[j] = '0' + (9-d);
        else res[i] = '0' + (9+d);
    }
    cout << res << endl;
    return 0;
}
