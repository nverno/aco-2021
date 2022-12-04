// -*- compile-command: "make d1" -*-
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    int cur = 0, mx = 0;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) cur = 0;
        else {
            cur += stoi(line);
            mx = max(mx, cur);
        }
    }
    cout << mx << endl;
    return 0;
}
