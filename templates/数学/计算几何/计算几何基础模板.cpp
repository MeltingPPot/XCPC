#include <bits/stdc++.h>
using namespace std;
using ld = long double;
constexpr ld EPS = 1e-12L;

int sgn(ld x) {
    return (x > EPS) - (x < -EPS);
}
struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {
    }
    Point operator+(Point p) const {
        return {x + p.x, y + p.y};
    }
    Point operator-(Point p) const {
        return {x - p.x, y - p.y};
    }
    Point operator*(ld k) const {
        return {x * k, y * k};
    }
};
ld dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}
ld cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
ld norm(Point a) {
    return sqrtl(dot(a, a));
}
Point projection(Point p, Point a, Point b) {
    Point v = b - a;
    return a + v * (dot(p - a, v) / dot(v, v));
}
