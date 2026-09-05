#include<bits/stdc++.h>
using namespace std;

long double determinant(vector<vector<long double>> a, long double eps = 1e-15L){
    long double ans = 1;
    int n = a.size();
    for(int i = 0; i < n; ++i){
        int p = i;
        for(int j = i; j < n; ++j)
            if(fabsl(a[j][i]) > fabsl(a[p][i]))
                p = j;
        if(fabsl(a[p][i]) < eps)
            return 0;
        if(p != i)
            swap(a[p], a[i]), ans = -ans;
        ans *= a[i][i];
        for(int j = i + 1; j < n; ++j){
            long double c = a[j][i] / a[i][i];
            for(int k = i + 1; k < n; ++k)
                a[j][k] -= c * a[i][k];
        }
    }
    return ans;
}
