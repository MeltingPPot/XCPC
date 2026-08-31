#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    vector<vector<int>> st;
    SparseTable(const vector<int> &a) {
        int n = a.size(), lg = __lg(n) + 1;
        st.assign(lg, a);
        for(int k = 1; k < lg; ++k) {
            st[k].resize(n - (1 << k) + 1);
            for(int i = 0; i < (int)st[k].size(); ++i)
                st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }
    int query(int l, int r) const {
        int k = __lg(r - l + 1);
        return max(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
