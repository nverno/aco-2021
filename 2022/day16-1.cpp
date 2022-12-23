// -*- compile-command: "make d16" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int maxN = 26*26, minutes = 30;
vector<int> g[maxN];
int rate[maxN];

vector<string> ids;
struct init_ids {
    init_ids() {
        for (char i = 'A'; i <= 'Z'; ++i) 
            // for (char j = 'A'; j <= 'Z'; ++j) 
                ids.push_back(string(1, i) + string(1, i));
        sort(ids.begin(), ids.end());
    }
} init_ids_;

int to_id(string s) {
    return lower_bound(begin(ids), end(ids), s) - begin(ids);
}

void parse_line(string line) {
    const int n = line.size();
    int u = to_id(line.substr(6, 2)),
      pos = line.find('=') + 1,
      val = 0;

    while (isdigit(line[pos])) 
        val = 10*val + (line[pos++]-'0');
    rate[u] = val;
    
    pos = line.find("valve");
    for (int i = pos + 6 + (line[pos+5] == 's'); i < n; i += 4) 
        g[u].push_back(to_id(line.substr(i, 2)));
}

int main(int argc, char *argv[]) {
    cout << endl;
    cout << "ids: ";
    copy(ids.begin(), ids.end(), ostream_iterator<decltype(ids[0])>(cout, " "));
    cout << endl;

    string line;
    while (getline(cin, line)) {
        parse_line(line);
    }
    cout << "rte: ";
    for (int i = 0; i < (int)ids.size(); ++i) {
        cout << setw(2) << rate[i] << ' ';
    }
    cout << endl;

    // cout << endl;
    // for (int i = 0; i < maxN; ++i) {
    //     if (g[i].size()) {
    //         cout << i << ": ";
    //         copy(g[i].begin(), g[i].end(), ostream_iterator<decltype(g[i][0])>(cout, " "));
    //         cout << endl;
    //     }
    // }
    // return 0;

    vector<vector<int>> dp(maxN, vector<int>(minutes+1, -1));
    dp[1][0] = 0;
    queue<tuple<int,int,bitset<maxN>,int>> q;
    q.push({1, 0, 0, 0});

    int res = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto [u, t, opened, score] = q.front(); q.pop();
            if (t == minutes) {
                res = max(res, score);
                continue;
            }
            if (t < minutes) {
                for (auto& v : g[u]) {
                    if (dp[v][t+1] < score) {
                        dp[v][t+1] = score;
                        q.push({v, t+1, opened, score});
                    }
                }
                if (opened[u]) continue;
                opened[u] = 1;
                int r = (minutes - t - 1) * rate[u];
                if (dp[u][t+1] < score + r) {
                    cout << "Minute " << ids[u] << " at time " << t+1 << ": " << r << '\n';
                    dp[u][t+1] = score + r;
                    q.push({u, t+1, opened, score+r});
                }
            }
        }
    }

    // for (int i = 0; i < maxN; ++i) {
    //     for (int j = 0; j < minutes; ++j) {
    //         res = max(res, dp[i][j]);
    //     }
    // }
    cout << res << '\n';
    return 0;
}
