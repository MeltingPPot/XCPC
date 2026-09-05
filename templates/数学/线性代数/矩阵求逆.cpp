#include<bits/stdc++.h>
using namespace std;

bool inverseMatrix(vector<vector<double>> a, vector<vector<double>> &inv, double eps = 1e-9){
    int n = a.size();
    inv.assign(n, vector<double>(n));
    for(int i = 0; i < n; ++i)
        inv[i][i] = 1;
    for(int i = 0; i < n; ++i){
        int p = i;
        for(int j = i; j < n; ++j)
            if(abs(a[j][i]) > abs(a[p][i]))
                p = j;
        if(abs(a[p][i]) < eps)
            return false;
        swap(a[i], a[p]);
        swap(inv[i], inv[p]);
        double d = a[i][i];
        for(int j = 0; j < n; ++j)
            a[i][j] /= d, inv[i][j] /= d;
        for(int j = 0; j < n; ++j)
            if(j != i){
                double c = a[j][i];
                for(int k = 0; k < n; ++k)
                    a[j][k] -= c * a[i][k], inv[j][k] -= c * inv[i][k];
            }
    }
    return true;
}
