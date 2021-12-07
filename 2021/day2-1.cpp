#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    string dir;
    int dx, x = 0, y = 0;
    while (cin >> dir >> dx) {
        if (dir == "forward") {
            x += dx;
        } else if (dir == "down") {
            y += dx;
        } else {
            y -= dx;
        }
    }
    cout << x*y << endl;
    return 0;
}
