#include <bits/stdc++.h>
using namespace std;

vector<int> sievePhi(int n) {
    vector<int> phi(n + 1), primes;
    vector<bool> composite(n + 1);
    if(n >= 1)
        phi[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!composite[i])
            primes.push_back(i), phi[i] = i - 1;
        for(int p : primes) {
            if(p > n / i)
                break;
            composite[i * p] = true;
            if(i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
        }
    }
    return phi;
}
