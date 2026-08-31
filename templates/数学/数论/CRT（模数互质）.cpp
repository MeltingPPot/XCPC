#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 extgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if(!b)
        return x = 1, y = 0, a;
    i64 g = extgcd(b, a % b, y, x);
    return y -= a / b * x, g;
}
i64 crt(const vector<i64> &rem, const vector<i64> &mod) {
    i64 product = 1;
    for(i64 m : mod)
        product *= m;
    __int128 ans = 0;
    for(int i = 0; i < (int)mod.size(); ++i) {
        i64 x, y, part = product / mod[i];
        extgcd(part, mod[i], x, y);
        ans = (ans + (__int128)rem[i] * part % product * x) % product;
    }
    return (ans % product + product) % product;
}
