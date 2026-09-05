#include<bits/stdc++.h>
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
};
ld cross(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}
vector<Point> minkowski(vector<Point> a, vector<Point> b){
    auto normalize = [](vector<Point> &p){
        int id = min_element(p.begin(), p.end(),
                             [](Point u, Point v){ return tie(u.y, u.x) < tie(v.y, v.x); }) -
                 p.begin();
        rotate(p.begin(), p.begin() + id, p.end());
    };
    normalize(a);
    normalize(b);
    int n = a.size(), m = b.size(), i = 0, j = 0;
    vector<Point> out = {a[0] + b[0]};
    while(i < n || j < m){
        Point u = i < n ? a[(i + 1) % n] - a[i] : Point{},
              v = j < m ? b[(j + 1) % m] - b[j] : Point{};
        ld c = cross(u, v);
        if(j == m || (i < n && c > 0))
            out.push_back(out.back() + u), ++i;
        else if(i == n || c < 0)
            out.push_back(out.back() + v), ++j;
        else
            out.push_back(out.back() + u + v), ++i, ++j;
    }
    out.pop_back();
    return out;
}
