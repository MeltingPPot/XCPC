#include<bits/stdc++.h>
using namespace std;

long long modPow(long long a, long long e, long long mod){
    long long r = 1 % mod;
    for(; e; e >>= 1, a = (__int128)a * a % mod)
        if(e & 1)
            r = (__int128)r * a % mod;
    return r;
}
long long inversePrime(long long a, long long prime){
    return modPow(a, prime - 2, prime);
}
vector<long long> inverseLinear(int n, long long prime){
    vector<long long> inv(n + 1);
    if(n >= 1)
        inv[1] = 1;
    for(int i = 2; i <= n; ++i)
        inv[i] = (prime - prime / i) * inv[prime % i] % prime;
    return inv;
}
