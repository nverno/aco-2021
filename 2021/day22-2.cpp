// -*- compile-command: "make d22" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

struct Seg {
    int v;
    vector<pair<int,int>> rs;
    Seg() {}
    Seg(string s, string dir) {
        assert(dir == "on" || dir == "off");
        v = dir == "on" ? 1 : 0;
        vector<string> parts;
        split(s, parts, ',');
        for (size_t i = 0; i < parts.size(); ++i) {
            auto &p = parts[i];
            size_t pos = 2;
            while (p[pos] == '-' || isdigit(p[pos])) ++pos;
            int a = stoi(p.substr(2, pos-2)),
                b = stoi(p.substr(pos+2)) + 1;
            assert(b > a);
            rs.push_back({ a, b });
        }
    }
};
ostream& operator<<(ostream& os, const Seg& s) {
    os << (s.v == 0 ? "off " : "on ");
    array<string,3> dims = {"x", "y", "z"};
    for (size_t i = 0; i < s.rs.size(); ++i) {
        os << dims[i] << "=" << s.rs[i].first << ".." << s.rs[i].second;
        if (i < s.rs.size()-1) os << ",";
    }
    return os;
}

using grid3d = vector<vector<vector<int>>>;

int main(int argc, char *argv[]) {
    vector<Seg> segs;
    array<set<int>,3> vals;
    array<unordered_map<ll,ll>,3> idx, ridx;

    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        size_t pos = line.find(" ");
        Seg seg(line.substr(pos+1), line.substr(0, pos));
        segs.push_back(seg);
        for (int i = 0; i < 3; ++i) {
            auto [b, e] = seg.rs[i];
            vals[i].insert(b);
            vals[i].insert(e);
        }
    }
    
    // normalize indicies
    for (int dim = 0; dim < 3; ++dim) {
        int i = 0;
        for (auto& v : vals[dim]) {
            ridx[dim][i] = v;
            idx[dim][v] = i++;
        }
    }

    const size_t mx = vals[0].size(), my = vals[1].size(), mz = vals[2].size();
    // cout << "dims: " << mx << "x" << my << "x" << mz << endl;

    grid3d mat(mx, vector<vector<int>>(my, vector<int>(mz)));
    for (auto& [v, dims] : segs) {
        auto [xi, xj] = dims[0];
        auto [yi, yj] = dims[1];
        auto [zi, zj] = dims[2];
        for (int i = idx[0][xi]; i < idx[0][xj]; ++i)
            for (int j = idx[1][yi]; j < idx[1][yj]; ++j)
                for (int k = idx[2][zi]; k < idx[2][zj]; ++k)
                    mat[i][j][k] = v;
    }

    auto volume = [&](int x, int y, int z) {
        return 1LL * (ridx[0][x+1] - ridx[0][x]) * (ll)(ridx[1][y+1] - ridx[1][y]) *
                (ll)(ridx[2][z+1] - ridx[2][z]);
    };

    ll res = 0;
    for (size_t i = 0; i < mx; ++i) {
        for (size_t j = 0; j < my; ++j) {
            for (size_t k = 0; k < mz; ++k) {
                if (mat[i][j][k])
                    res += volume(i, j, k);
            }
        }
    }

    cout << res << endl;
    return 0;
}
