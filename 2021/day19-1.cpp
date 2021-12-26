// -*- compile-command: "make d19" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
#include "../lib/point.hpp"
using namespace std;
using Point = Point3D;

struct Scanner {
    int id;
    vector<Point> ps;
    vector<set<Point>> rots;

    Scanner(int i): id(0) {}
    void insert(vector<int>& v) { ps.push_back(Point(v)); }
    
    void calcRotations() {
        if (rots.size() == 24) return;
        set<Point> cur(ps.begin(), ps.end()), nxt;
        for (int flip = 0; flip < 2; ++flip) {
            for (int i = 0; i < 3; ++i) {
                nxt.clear();
                for (auto& e : cur) nxt.insert(e.rotateX());
                rots.push_back(nxt);
                swap(cur, nxt);
                for (int j = 0; j < 3; ++j) {
                    nxt.clear();
                    for (auto& e : cur) nxt.insert(e.rotateZ());
                    rots.push_back(nxt);
                    swap(cur, nxt);
                }
            }
            nxt.clear();
            for (auto& e : cur) nxt.insert(e.flipY());
            rots.push_back(nxt);
            swap(cur, nxt);
        }
    }

    bool addBeacons(set<Point>& beacons) {
        calcRotations();
        for (auto& b : beacons) {
            for (auto& r : rots) {
                for (auto& origin : r) {
                    Point diff = b - origin;
                    int cnt = 0;
                    for (auto& p : r) {
                        if (beacons.count(p + diff)) ++cnt;
                        if (cnt >= 12) {
                            for (auto& e : r) beacons.insert(e + diff);
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};
ostream& operator<<(ostream& os, const Scanner *s) {
    os << "scanner: " << s->id << endl;
    for (auto& p : s->ps) os << p << endl;
    return os;
}

int main(int argc, char *argv[]) {
    queue<Scanner*> q;
    Scanner *cur = nullptr;
    set<Point> beacons;
    vector<int> point;
    string line;
    int idx = 0;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        if (line.find("scanner") != string::npos) {
            if (idx == 0) idx++;
            else {
                cur = new Scanner(idx++);
                q.push(cur);
            }
        } else {
            split(line, point, ',');
            if (!cur) beacons.insert(Point(point));
            else cur->insert(point);
        }
    }
    
    while (!q.empty()) {
        cur = q.front(); q.pop();
        if (!cur->addBeacons(beacons))
            q.push(cur);
    }

    cout << "beacons: \n";
    for (auto& p : beacons) {
        cout << p << endl;
    }
    cout << beacons.size() << endl;
    return 0;
}
