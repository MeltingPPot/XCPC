#include<bits/stdc++.h>
using namespace std;

vector<int> sieveDivisorCount(int n){
    vector<int> d(n + 1), exponent(n + 1), primes;
    vector<bool> composite(n + 1);
    if(n >= 1)
        d[1] = 1;
    for(int i = 2; i <= n; ++i){
        if(!composite[i])
            primes.push_back(i), d[i] = 2, exponent[i] = 1;
        for(int p : primes){
            if(p > n / i)
                break;
            composite[i * p] = true;
            if(i % p == 0){
                exponent[i * p] = exponent[i] + 1;
                d[i * p] = d[i] / (exponent[i] + 1) * (exponent[i * p] + 1);
                break;
            }
            exponent[i * p] = 1;
            d[i * p] = d[i] * 2;
        }
    }
    return d;
}
