// -*- compile-command: "make d7" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int maxN = 100;
struct dir {
    int sz;
    string name;
    dir *par;
    vector<dir*> sub;
    dir(dir* p = nullptr, string nm = ""): sz(0), name(nm), par(p) {}
} root;

dir *cur = &root;

void cd(string d) {
    if (d == "..") {
        assert(cur->par);
        cur = cur->par;
    } else {
        for (auto& ch : cur->sub) {
            if (ch->name == d) {
                cur = ch;
                break;
            }
        }
    }
}

int dfs(dir *d, int& res) {
    int s = d->sz;
    for (auto& ch : d->sub) {
        s += dfs(ch, res);
    }
    if (s <= 1e5) res += s;
    return s;
}

int main(int argc, char *argv[]) {
    string line;
    while (getline(cin, line)) {
        vector<string> parts;
        split(line, parts, ' ');

        if (parts[0] == "$") {
            if (parts[1] == "cd") {
                assert(parts.size() == 3);
                cd(parts[2]);
            }
            else assert(parts[1] == "ls");
        } else {
            if (parts[0] == "dir") {
                cur->sub.push_back(new dir(cur, parts[1]));
            } else {
                assert(isdigit(parts[0][0]));
                cur->sz += stoi(parts[0]);
            }
        }
    }
    int res = 0;
    dfs(&root, res);
    cout << res << '\n';
    return 0;
}
