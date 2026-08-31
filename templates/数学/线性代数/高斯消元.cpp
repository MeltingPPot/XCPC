#include <bits/stdc++.h>
using namespace std;

// 增广矩阵 a，返回 0/1/2（无解/唯一解/无穷多解）。
int gauss(vector<vector<double>> a, vector<double> &ans, double eps = 1e-9) {
    int n = a.size(), m = a[0].size() - 1, row = 0;
    vector<int> where(m, -1);
    for(int col = 0; col < m && row < n; ++col) {
        int sel = row;
        for(int i = row; i < n; ++i)
            if(abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if(abs(a[sel][col]) < eps)
            continue;
        swap(a[sel], a[row]);
        where[col] = row;
        for(int i = 0; i < n; ++i)
            if(i != row) {
                double c = a[i][col] / a[row][col];
                for(int j = col; j <= m; ++j)
                    a[i][j] -= c * a[row][j];
            }
        ++row;
    }
    ans.assign(m, 0);
    for(int i = 0; i < m; ++i)
        if(where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for(int i = 0; i < n; ++i) {
        double lhs = 0;
        for(int j = 0; j < m; ++j)
            lhs += abs(a[i][j]);
        if(lhs < eps && abs(a[i][m]) > eps)
            return 0;
    }
    return row == m ? 1 : 2;
}
