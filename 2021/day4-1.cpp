#include <bits/stdc++.h>
using namespace std;

struct Board {
    vector<int> rows, cols;
    std::unordered_map<int,pair<int,int>> idx;
    int sum;
    Board(): sum(0) {
        rows.resize(5,5);
        cols.resize(5,5);
    }
    bool read(istream& is) {
        int r = 0, num;
        bool ok = true;
        while (ok && r < 5) {
            for (int c = 0; ok && c < 5; ++c) {
                if (!(cin >> num)) ok = false;
                idx[num] = {r, c};
                sum += num;
            }
            ++r;
        }
        return ok;
    }
    int draw(int x) {
        if (idx.count(x)) {
            auto [r, c] = idx[x];
            rows[r]--;
            cols[c]--;
            sum -= x;
            if (rows[r] == 0 || cols[c] == 0)
                return sum * x;
        }
        return -1;
    }
};

int main(int argc, char *argv[]) {
    string line, num;
    getline(cin, line);
    istringstream iss(line);

    vector<int> nums;
    while (getline(iss, num, ','))
        nums.push_back(stoi(num));

    vector<Board> boards(120);
    for (auto& b : boards) b.read(cin);

    for (auto& x : nums) {
        for (auto& b : boards) {
            int res = b.draw(x);
            if (res != -1) {
                cout << res << endl;
                return 0;
            }
        }
    }
    return 0;
}
