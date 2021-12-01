#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    int res = 0, cur = 0, a=0, b=0, c=0, i = 0;
    while (cin >> c) {
        if (i++ >= 3 && a+b+c > cur) ++res;
        cur = a + b + c;
        a=b; b=c;
    }
    cout << res;
    return 0;
}
