#include<bits/stdc++.h>
using namespace std;
using ld = long double;
struct Point {
    ld x, y;
    Point operator-(Point p) const {
        return {x - p.x, y - p.y};
    }
};
ld cross(Point a, Point b){
    return a.x * b.y - a.y * b.x;
}
ld dist2(Point a, Point b){
    ld x = a.x - b.x, y = a.y - b.y;
    return x * x + y * y;
}
ld convexDiameter2(const vector<Point> &p){
    int n = p.size();
    if(n < 2)
        return 0;
    int j = 1;
    ld ans = 0;
    for(int i = 0; i < n; ++i){
        int ni = (i + 1) % n;
        while(fabsl(cross(p[ni] - p[i], p[(j + 1) % n] - p[i])) >
              fabsl(cross(p[ni] - p[i], p[j] - p[i])))
            j = (j + 1) % n;
        ans = max({ans, dist2(p[i], p[j]), dist2(p[ni], p[j])});
    }
    return ans;
}
