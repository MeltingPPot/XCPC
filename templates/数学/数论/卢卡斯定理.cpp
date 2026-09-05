#include<bits/stdc++.h>
using namespace std;

long long lucasPow(long long a, long long e, long long p){
    long long r = 1;
    for(; e; e >>= 1, a = a * a % p)
        if(e & 1)
            r = r * a % p;
    return r;
}
long long combSmall(long long n, long long k, long long p){
    if(k > n)
        return 0;
    long long r = 1;
    for(long long i = 1; i <= k; ++i)
        r = r * (n - k + i) % p * lucasPow(i, p - 2, p) % p;
    return r;
}
long long lucas(long long n, long long k, long long prime){
    return !k ? 1
              : combSmall(n % prime, k % prime, prime) * lucas(n / prime, k / prime, prime) % prime;
}
