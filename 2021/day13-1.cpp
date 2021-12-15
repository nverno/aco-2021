// -*- compile-command: "make d13" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

void fold(string& line, vector<vector<int>>& points) {
    size_t pos;
    if ((pos = line.find("=")) != string::npos) {
        int v = stoi(line.substr(pos+1));
        if (line[pos-1] == 'x') {
            for (auto& p : points)
                if (p[0] > v)
                    p[0] = v - (p[0]-v);
        } else {
            for (auto& p : points)
                if (p[1] > v)
                    p[1] = v - (p[1]-v);
        }
    }
}

int main(int argc, char *argv[]) {
    vector<vector<int>> points;
    vector<int> pnt;
    string line;
    bool done = false;
    while (!done && getline(cin, line)) {
        if (line.find("fold") != string::npos) {
            done = true;
            fold(line, points);
        } else {
            split(line, pnt, ',');
            if (pnt.size())
                points.push_back(pnt);
        }
    }

    set<pair<int,int>> res;
    for (auto& p : points)
        res.insert({ p[0], p[1] });
    cout << res.size() << endl;
    return 0;
}
