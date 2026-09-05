#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 MOD = 998244353;

void fwtOr(vector<i64> &a, bool inverse){
    for(int len = 1; len < (int)a.size(); len <<= 1)
        for(int i = 0; i < (int)a.size(); i += len << 1)
            for(int j = 0; j < len; ++j){
                if(!inverse)
                    a[i + j + len] = (a[i + j + len] + a[i + j]) % MOD;
                else
                    a[i + j + len] = (a[i + j + len] - a[i + j] + MOD) % MOD;
            }
}
