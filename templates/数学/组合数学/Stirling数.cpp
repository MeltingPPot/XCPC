#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> stirlingSecond(int n, long long mod) {
    vector<vector<long long>> s(n + 1, vector<long long>(n + 1));
    s[0][0] = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            s[i][j] = (s[i - 1][j - 1] + j * s[i - 1][j]) % mod;
    return s;
}
