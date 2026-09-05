#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Matrix {
    int n;
    i64 mod;
    vector<vector<i64>> a;
    Matrix(int n, i64 mod, bool identity = false) : n(n), mod(mod), a(n, vector<i64>(n)){
        if(identity)
            for(int i = 0; i < n; ++i)
                a[i][i] = 1;
    }
    Matrix operator*(const Matrix &b) const {
        Matrix c(n, mod);
        for(int i = 0; i < n; ++i)
            for(int k = 0; k < n; ++k)
                if(a[i][k])
                    for(int j = 0; j < n; ++j)
                        c.a[i][j] = (c.a[i][j] + (__int128)a[i][k] * b.a[k][j]) % mod;
        return c;
    }
};
Matrix matrixPow(Matrix a, long long e){
    Matrix r(a.n, a.mod, true);
    for(; e; e >>= 1, a = a * a)
        if(e & 1)
            r = r * a;
    return r;
}
