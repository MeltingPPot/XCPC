#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 MOD = 998244353;

i64 lagPow(i64 a, i64 e) {
    i64 r = 1;
    for(; e; e >>= 1, a = a * a % MOD)
        if(e & 1)
            r = r * a % MOD;
    return r;
}
i64 lagrange(const vector<i64> &x, const vector<i64> &y, i64 k) {
    int n = x.size();
    i64 ans = 0;
    for(int i = 0; i < n; ++i) {
        i64 num = 1, den = 1;
        for(int j = 0; j < n; ++j)
            if(i != j) {
                num = num * ((k - x[j]) % MOD + MOD) % MOD;
                den = den * ((x[i] - x[j]) % MOD + MOD) % MOD;
            }
        ans = (ans + y[i] * num % MOD * lagPow(den, MOD - 2)) % MOD;
    }
    return ans;
}
