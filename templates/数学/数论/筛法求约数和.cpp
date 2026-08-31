#include <bits/stdc++.h>
using namespace std;

vector<long long> sieveDivisorSum(int n) {
    vector<long long> sum(n + 1), geometric(n + 1);
    vector<int> primes;
    vector<bool> composite(n + 1);
    if(n >= 1)
        sum[1] = geometric[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!composite[i])
            primes.push_back(i), sum[i] = geometric[i] = i + 1LL;
        for(int p : primes) {
            if(p > n / i)
                break;
            composite[i * p] = true;
            if(i % p == 0) {
                geometric[i * p] = geometric[i] * p + 1;
                sum[i * p] = sum[i] / geometric[i] * geometric[i * p];
                break;
            }
            geometric[i * p] = p + 1LL;
            sum[i * p] = sum[i] * geometric[i * p];
        }
    }
    return sum;
}
