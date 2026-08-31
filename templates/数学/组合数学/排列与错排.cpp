#include <bits/stdc++.h>
using namespace std;

vector<long long> derangements(int n, long long mod) {
    vector<long long> d(n + 1);
    if(n >= 0)
        d[0] = 1;
    if(n >= 1)
        d[1] = 0;
    for(int i = 2; i <= n; ++i)
        d[i] = (i - 1LL) * (d[i - 1] + d[i - 2]) % mod;
    return d;
}
