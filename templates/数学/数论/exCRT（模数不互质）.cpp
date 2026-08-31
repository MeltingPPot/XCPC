#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 exgcdCrt(i64 a, i64 b, i64 &x, i64 &y) {
    if(!b)
        return x = 1, y = 0, a;
    i64 g = exgcdCrt(b, a % b, y, x);
    return y -= a / b * x, g;
}
bool mergeCRT(i64 a1, i64 m1, i64 a2, i64 m2, i64 &a, i64 &m) {
    i64 x, y, g = exgcdCrt(m1, m2, x, y), delta = a2 - a1;
    if(delta % g)
        return false;
    i64 mod = m2 / g, k = (__int128)(delta / g) * x % mod;
    m = m1 * mod;
    a = ((i64)((__int128)m1 * k % m) + a1) % m;
    if(a < 0)
        a += m;
    return true;
}
