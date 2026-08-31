#include <bits/stdc++.h>
using namespace std;

vector<long long> factorize(long long n) {
    vector<long long> factors;
    for(long long p = 2; p <= n / p; ++p)
        if(n % p == 0) {
            factors.push_back(p);
            while(n % p == 0)
                n /= p;
        }
    if(n > 1)
        factors.push_back(n);
    return factors; // 不重复的质因子
}
