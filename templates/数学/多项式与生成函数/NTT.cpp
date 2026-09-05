#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 MOD = 998244353, G = 3;

i64 nttPow(i64 a, i64 e){
    i64 r = 1;
    for(; e; e >>= 1, a = a * a % MOD)
        if(e & 1)
            r = r * a % MOD;
    return r;
}
void ntt(vector<i64> &a, bool invert){
    int n = a.size();
    for(int i = 1, j = 0; i < n; ++i){
        int bit = n >> 1;
        for(; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if(i < j)
            swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1){
        i64 wlen = nttPow(G, (MOD - 1) / len);
        if(invert)
            wlen = nttPow(wlen, MOD - 2);
        for(int i = 0; i < n; i += len){
            i64 w = 1;
            for(int j = 0; j < len / 2; ++j){
                i64 u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + len / 2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }
    if(invert){
        i64 invN = nttPow(n, MOD - 2);
        for(i64 &x : a)
            x = x * invN % MOD;
    }
}
vector<i64> multiply(vector<i64> a, vector<i64> b){
    int need = a.size() + b.size() - 1, n = 1;
    while(n < need)
        n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for(int i = 0; i < n; ++i)
        a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}
