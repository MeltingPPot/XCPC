#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 MOD = 998244353;

void fwtXor(vector<i64> &a, bool inverse) {
    for(int len = 1; len < (int)a.size(); len <<= 1)
        for(int i = 0; i < (int)a.size(); i += len << 1)
            for(int j = 0; j < len; ++j) {
                i64 x = a[i + j], y = a[i + j + len];
                a[i + j] = (x + y) % MOD;
                a[i + j + len] = (x - y + MOD) % MOD;
            }
    if(inverse) {
        i64 inv = 1;
        for(int n = a.size(); n > 1; n >>= 1)
            inv = inv * ((MOD + 1) / 2) % MOD;
        for(i64 &x : a)
            x = x * inv % MOD;
    }
}
