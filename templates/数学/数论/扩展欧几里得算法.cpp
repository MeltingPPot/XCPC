#include <bits/stdc++.h>
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if(!b)
        return x = (a >= 0 ? 1 : -1), y = 0, abs(a);
    long long g = exgcd(b, a % b, y, x);
    return y -= a / b * x, g;
}
