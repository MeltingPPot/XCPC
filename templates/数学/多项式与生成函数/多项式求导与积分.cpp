#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 MOD = 998244353;

i64 polynomialPower(i64 a, i64 e){
    i64 r = 1;
    for(; e; e >>= 1, a = a * a % MOD)
        if(e & 1)
            r = r * a % MOD;
    return r;
}
vector<i64> deriv(const vector<i64> &a){
    vector<i64> b(max(0, (int)a.size() - 1));
    for(int i = 1; i < (int)a.size(); ++i)
        b[i - 1] = a[i] * i % MOD;
    return b;
}
vector<i64> integ(const vector<i64> &a){
    vector<i64> b(a.size() + 1);
    for(int i = 0; i < (int)a.size(); ++i)
        b[i + 1] = a[i] * polynomialPower(i + 1, MOD - 2) % MOD;
    return b;
}
