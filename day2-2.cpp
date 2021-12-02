#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main(int argc, char *argv[]) {
    string dir;
    ll dx, x = 0, y = 0, aim = 0;
    while (cin >> dir >> dx) {
        if (dir == "forward") {
            x += dx;
            y += dx * aim;
        } else if (dir == "down") {
            aim += dx;
        } else {
            aim -= dx;
        }
    }
    cout << y*x << endl;
    return 0;
}
