#include<bits/stdc++.h>
using namespace std;

long long catPow(long long a, long long e, long long mod){
    long long result = 1;
    for(; e; e >>= 1, a = a * a % mod){
        if(e & 1)
            result = result * a % mod;
    }
    return result;
}

long long catalan(int n, long long mod, const vector<long long> &fac,
                  const vector<long long> &ifac){
    return fac[2 * n] * ifac[n] % mod * ifac[n] % mod * catPow(n + 1, mod - 2, mod) % mod;
}
