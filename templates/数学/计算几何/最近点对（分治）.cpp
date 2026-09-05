#include<bits/stdc++.h>
using namespace std;
using ld = long double;
struct Point {
    ld x, y;
};
ld distance2(Point a, Point b){
    ld x = a.x - b.x, y = a.y - b.y;
    return x * x + y * y;
}
ld closestPair2(vector<Point> points){
    sort(points.begin(), points.end(), [](Point a, Point b){ return a.x < b.x; });
    ld ans = numeric_limits<ld>::infinity();
    for(int i = 0; i < (int)points.size(); ++i)
        for(int j = i - 1;
            j >= 0 && (points[i].x - points[j].x) * (points[i].x - points[j].x) < ans; --j)
            ans = min(ans, distance2(points[i], points[j]));
    return ans;
}
