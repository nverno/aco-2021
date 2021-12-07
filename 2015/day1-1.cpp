#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    int res = 0;
    char c;
    while (cin >> c)
        res += c == '(' ? 1 : -1;
    cout << res << endl;
    return 0;
}
