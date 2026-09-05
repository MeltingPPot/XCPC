#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200000 + 5;
int n, dfn[MAXN], fa[MAXN];

struct St {
    int st[MAXN][25];
    int dfnmin(int x, int y) {
        if (dfn[x] < dfn[y]) return x;
        return y; 
    }
    void init() {
        int t = std::__lg(n) + 1;
        for (int i = 1; i <= n; i++) st[dfn[i]][0] = fa[i];
        for (int j = 1; j <= t; j++) {
            for (int i = 1; i + (1 << (j - 1))<= n; i++) {
                st[i][j] = dfnmin(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int query(int l, int r) {
        int t = std::__lg(r - l + 1);
        return dfnmin(st[l][t], st[r - (1 << t) + 1][t]);
    }
}st;

int lca(int x, int y) {
    if (x == y) return x;
    if (dfn[x] > dfn[y]) std::swap(x, y);
    return st.query(dfn[x] + 1, dfn[y]);
}
