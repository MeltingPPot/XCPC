#include <bits/stdc++.h>
using namespace std;

long long qpow(long long a, long long e, long long mod) {
    long long ans = 1 % mod;
    for(a %= mod; e; e >>= 1, a = (__int128)a * a % mod)
        if(e & 1)
            ans = (__int128)ans * a % mod;
    return ans;
}
