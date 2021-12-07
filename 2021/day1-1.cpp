#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    int res = 0, prev, cur;
    int i = 0;
    while (cin >> cur) {
        if (i++ > 0 && cur - prev > 0) ++res;
        prev = cur;
    }
    cout << res;
    return 0;
}
