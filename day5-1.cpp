#include <bits/stdc++.h>
using namespace std;

const int HORZ = 0, VERT = 1;
vector<int> readSeg(string& l) {
    vector<int> vals;
    string cur;
    for (size_t i = 0; i < l.size(); ++i) {
        if (isdigit(l[i])) cur += l[i];
        else if (cur.size()) {
            vals.push_back(stoi(cur));
            cur.clear();
        }
    }
    int a = vals[0], b = vals[1], c = vals[2], d = stoi(cur);
    if (a == c)
        return {a, min(b, d), max(b, d), VERT};
    if (b == d)
        return {b, min(a, c), max(a, c), HORZ};
    return {};
}

int main(int argc, char *argv[]) {
    vector<vector<int>> horz, vert;
    string line;
    while (getline(cin, line)) {
        vector<int> seg = readSeg(line);
        if (seg.empty()) continue;

        if (seg.back() == HORZ) horz.push_back(seg);
        else vert.push_back(seg);
    }

    // brute
    vector<vector<int>> mat(1000, vector<int>(1000));
    for (auto& v : horz) {
        int y = v[0], xi = v[1], xj = v[2];
        for (int i = xi; i <= xj; ++i) {
            mat[i][y]++;
        }
    }

    for (auto& v : vert) {
        int x = v[0], yi = v[1], yj = v[2];
        for (int j = yi; j <= yj; ++j) {
            mat[x][j]++;
        }
    }

    int res = 0;
    for (auto& r : mat) {
        for (auto& e : r) {
            if (e > 1) ++res;
        }
    }

    cout << res << endl;
    return 0;
}
