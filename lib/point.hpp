#pragma once
#include "aoc.hpp"
extern void split(std::string&, std::vector<int>&, char c);

struct Point3D {
    int x, y, z;
    Point3D(std::vector<int>& vec): x(vec[0]), y(vec[1]), z(vec[2]) {}
    Point3D(int _x, int _y, int _z): x(_x), y(_y), z(_z) {}
    Point3D(std::string& line, char sep=',') {
        std::vector<int> parts;
        split(line, parts, sep);
        x = parts[0]; y = parts[1]; z = parts[2];
    }
    Point3D shift(const Point3D& o, int sign=1) const {
        return {sign*o.x+x, sign*o.y+y, sign*o.z+z};
    }
    Point3D operator-(const Point3D& o) const {
        return Point3D(x-o.x, y-o.y, z-o.z);
    }
    Point3D operator+(const Point3D& o) const {
        return Point3D(x+o.x, y+o.y, z+o.z);
    }
    // rotate around X-axis (rolling forward when looking down y-axis)
    Point3D rotateX() const { return Point3D(x, z, -y); }
    // rotate around Z-axis (counter-clockwise from above)
    Point3D rotateZ() const { return Point3D(-y, x, z); }
    // rotate around Y-axis (ccw looking down y-axis)
    Point3D rotateY() const { return Point3D(-z, y, x); }
    // y => -y
    Point3D flipY() const { return Point3D(-z, -y, -x); }
    int manhattan(const Point3D& o) const {
        return abs(o.x-x) + abs(o.y-y) + abs(o.z-z);
    }
};
std::ostream& operator<<(std::ostream& os, const Point3D& p) {
    os << p.x << "," << p.y << "," << p.z;
    return os;
}
bool operator<(const Point3D& a, const Point3D& b) {
    return std::tie(a.x, a.y, a.z) < std::tie(b.x, b.y, b.z);
}
