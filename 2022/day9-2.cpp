// -*- compile-command: "make d9" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int SZ = 10;
const int TL = 9;

struct point {
    int x, y;
    point(): x(0), y(0) {}
    point(int xx, int yy): x(xx), y(yy) {}
    point& operator+=(const point& o) { x += o.x; y += o.y; return *this; }
    point& operator-=(const point& o) { x -= o.x; y -= o.y; return *this; }
    point& operator=(const point& o) { x = o.x; y = o.y; return *this; }
};
ostream& operator<<(ostream& os, const point& p) { return os << p.x << ' ' << p.y; }
inline point operator-(const point& a, const point& b) { return point(a.x - b.x, a.y - b.y); }
inline point operator+(const point& a, const point& b) { return point(a.x + b.x, a.y + b.y); }
inline bool operator<(const point& a, const point& b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

int sgn(int v) { return (0 < v) - (v < 0); }
point sgn(const point& p) { return point(sgn(p.x), sgn(p.y)); }

map<char,point> direction = {{'U', point(-1,0)}, {'D', point(1,0)}, {'L', point(0,-1)}, {'R', point(0,1)}};

int main(int argc, char *argv[]) {
    array<point,SZ> rope;
    set<point> seen{rope.back()};

    char dir;
    int dist;
    while (cin >> dir >> dist) {
        auto d = direction[dir];
        while (dist--) {
            rope[0] += d;
            for (int i = 1; i < SZ; ++i) {
                point diff = rope[i] - rope[i-1];
                if (max(abs(diff.x), abs(diff.y)) > 1) 
                    diff -= sgn(diff);
                rope[i] = rope[i-1] + diff;
            }
            seen.insert(rope.back());
        }
    }

    cout << seen.size() << '\n';
    return 0;
}
