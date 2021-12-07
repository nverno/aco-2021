#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    int f = 1, lvl = 0;
    char c;
    while (cin >> c) {
        lvl += (c == '(' ? 1 : -1);
        if (lvl < 0) {
            cout << f << endl;
            break;
        }
        f++;
    }
    return 0;
}
