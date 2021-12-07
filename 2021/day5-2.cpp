#include <bits/stdc++.h>
using namespace std;

tuple<int,int,int,int> readSeg(string& l) {
    vector<int> vals;
    string cur;
    for (size_t i = 0; i < l.size(); ++i) {
        if (isdigit(l[i])) cur += l[i];
        else if (cur.size()) {
            vals.push_back(stoi(cur));
            cur.clear();
        }
    }
    int x1 = vals[0], y1 = vals[1], x2 = vals[2], y2 = stoi(cur);
    return {x1, x2, y1, y2};
}

int main(int argc, char *argv[]) {
    constexpr int SZ = 1000;
    vector<vector<int>> mat(SZ, vector<int>(SZ));

    string line;
    while (getline(cin, line)) {
        auto [x1, x2, y1, y2] = readSeg(line);
        int dx = x1 == x2 ? 0 : x1 < x2 ? 1 : -1,
            dy = y1 == y2 ? 0 : y1 < y2 ? 1 : -1;

        for (; !(x1 == x2 && y1 == y2); x1 += dx, y1 += dy)
            mat[x1][y1]++;

        mat[x2][y2]++;
    }

    int res = 0;
    for (auto& r : mat)
        for (auto& e : r)
            if (e > 1) ++res;

    cout << res << endl;
    return 0;
}
