#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Combinatorics {
    i64 mod;
    vector<i64> fac, ifac;
    i64 pow(i64 a, i64 e) const {
        i64 r = 1;
        for(; e; e >>= 1, a = a * a % mod)
            if(e & 1)
                r = r * a % mod;
        return r;
    }
    Combinatorics(int n, i64 mod) : mod(mod), fac(n + 1, 1), ifac(n + 1){
        for(int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = pow(fac[n], mod - 2);
        for(int i = n; i; --i)
            ifac[i - 1] = ifac[i] * i % mod;
    }
    i64 C(int n, int k) const {
        return k < 0 || k > n ? 0 : fac[n] * ifac[k] % mod * ifac[n - k] % mod;
    }
};
