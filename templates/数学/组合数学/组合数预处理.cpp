#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> pascal(int n, long long mod = 0) {
    vector<vector<long long>> c(n + 1, vector<long long>(n + 1));
    for(int i = 0; i <= n; ++i) {
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++j)
            c[i][j] = mod ? (c[i - 1][j - 1] + c[i - 1][j]) % mod : c[i - 1][j - 1] + c[i - 1][j];
    }
    return c;
}
