// -*- compile-command: "make d7" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    const int mask = 0xFFFF;
    std::unordered_map<string,uint16_t> vals;
    vals["1"] = 1;
    // override previous a -> b
    vals["b"] = 16076;
    
    vector<vector<string>> cmds, tmp;
    vector<string> cmd;
    string line;
    while (getline(cin, line)) {
        split(line, cmd);
        if (cmd.back() == "b") continue;  // skip override
        if (isdigit(cmd[0][0]) && cmd[1] == "->")
            vals[cmd[2]] = (uint16_t)stoi(cmd[0]);
        else 
            cmds.push_back(cmd);
    }

    while (!cmds.empty()) {
        int prev = cmds.size();
        tmp.clear();
        for (auto& c : cmds) {
            if (c[0] == "NOT" && vals.count(c[1])) {
                vals[c[3]] = ~ vals[c[1]];
            } else if (c[1] == "->" && vals.count(c[0])) {
                vals[c[2]] = vals[c[0]];
            } else if (c[1] == "AND" && vals.count(c[0]) && vals.count(c[2])) {
                vals[c[4]] = vals[c[0]] & vals[c[2]];
            } else if (c[1] == "OR" && vals.count(c[0]) && vals.count(c[2])) {
                vals[c[4]] = vals[c[0]] | vals[c[2]];
            } else if (c[1] == "RSHIFT" && vals.count(c[0])) {
                vals[c[4]] = vals[c[0]] >> (uint16_t)stoi(c[2]);
            } else if (c[1] == "LSHIFT" && vals.count(c[0])) {
                vals[c[4]] = vals[c[0]] << (uint16_t)stoi(c[2]);
            } else {
                tmp.push_back(c);
            }
        }
        swap(tmp, cmds);
        if (cmds.size() == prev) break;
    }

    // for (auto& [e, v] : vals)
    //     cout << e << ": " << v << endl;

    cout << (uint16_t)vals["a"] << endl;
    return 0;
}
