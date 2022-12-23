// -*- compile-command: "make d17" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;
#define ll long long

const vector<string> rocks[5] = {
    {
        "####"
    }, {
        ".#.",
        "###",
        ".#."
    }, {
        "..#",
        "..#",
        "###",
    }, {
        "#",
        "#",
        "#",
        "#",
    }, {
        "##",
        "##",
    },
};

map<tuple<int,int,string>,ll> seen;
// ll n = 1'000'000'000'000;
int n = 500000000;
const int WIDTH = 7, maxH = n * 3 + 5;
vector<string> g(maxH, string(WIDTH, '.'));
string dirs;
int di = 0;

bool can_move(int x, int y, int dx, const vector<string>& rock) {
    int w = rock[0].size(),
        h = rock.size();
    if (y+h > maxH || x+dx < 0 || x+w+dx > WIDTH) return false;
    for (int i = 0; i < h; ++i) {
        int yy = y + i;
        for (int j = 0; j < w; ++j) {
            if (rock[i][j] != '#') continue;
            int xx = x + j + dx;
            if (g[yy][xx] != '.')
                return false;
        }
    }
    return true;
}

void drop(int& x, int& y, const vector<string>& rock) {
    bool ok = true;
    int width = rock[0].size(),
           ht = rock.size();
    while (ok) {
        int dx = dirs[di] == '<' ? -1 : 1;
        if (can_move(x, y, dx, rock)) 
            x += dx;
        if (can_move(x, y+1, 0, rock))
            ++y;
        else ok = false;
        di = (di + 1) % dirs.size();
    }
    for (int i = 0; i < ht; ++i) {
        int yy = y + i;
        for (int j = 0; j < width; ++j) {
            if (rock[i][j] != '#') continue;
            int xx = x + j;
            g[yy][xx] = '#';
        }
    }
}

int main(int argc, char *argv[]) {
    cin >> dirs;

    int h = maxH, idx = 0;
    int cnt = 0;
    while (n--) {
        auto& rock = rocks[idx];
        int y = h - rock.size() - 3, x = 2;
        string state;
        for (int i = y+rock.size()+3; i < min(maxH, y+(int)rock.size()+6); ++i) {
            state += g[i];
        }
        if (seen.count({idx, di, state})) {
            cout << "cycle: " << cnt << '\n';
            return 0;
        }
        drop(x, y, rock);
        h = min(h, y);
        seen[{idx, di, state}] = h;
        idx = (idx + 1) % 5;
        ++cnt;
    }

    // cout << '\n';
    // for (auto& r : g) {
    //     cout << r << '\n';
    // }

    cout << maxH - h << '\n';
    return 0;
}
