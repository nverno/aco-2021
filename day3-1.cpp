#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    vector<int> cnt;
    string cur;
    cin >> cur;
    int sz = cur.size(), n = 1;
    cnt.resize(sz);

    while (cin >> cur) {
        for (int i = 0; i < sz; ++i)
            cnt[i] += cur[i]-'0';
        ++n;
    }
    int gamma = 0, eps = 0, p = 1;
    for (int i = sz-1; i >= 0; --i) {
        if (cnt[i] > n/2) gamma += p;
        else eps += p;
        p <<= 1;
    }
    cout << eps * gamma << endl;
    return 0;
}
