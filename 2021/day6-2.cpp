#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    string num;

    const int days = 256;
    vector<ll> dp(days + 1);
    ll res = 0;
    while (getline(iss, num, ',')) {
        int n = stoi(num);
        res++;
        dp[n+1]++;
    }

    for (int i = 1; i <= days; ++i) {
        res += dp[i];
        if (i+9 <= days)
            dp[i+9] += dp[i];
        if (i+7 <= days)
            dp[i+7] += dp[i];
    }
    
    cout << res << endl;
    return 0;
}
