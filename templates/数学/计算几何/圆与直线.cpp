#include <bits/stdc++.h>
using namespace std;
using ld = long double;
struct Point {
    ld x, y;
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
struct Circle {
    Point o;
    ld r;
};
vector<Point> lineCircleIntersection(Point a, Point b, Circle c) {
    Point v = b - a;
    ld t = dot(c.o - a, v) / dot(v, v);
    Point h = a + v * t;
    ld d2 = dot(h - c.o, h - c.o), r2 = c.r * c.r;
    if(d2 > r2 + 1e-12L)
        return {};
    if(fabsl(d2 - r2) <= 1e-12L)
        return {h};
    ld k = sqrtl((r2 - d2) / dot(v, v));
    return {h + v * k, h - v * k};
}
