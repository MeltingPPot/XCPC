#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200000 + 5;
vector<int> G[MAXN];
int siz[MAXN], fa[MAXN], dep[MAXN], son[MAXN], top[MAXN];

void dfs1(int u, int f) {
    siz[u] = 1; fa[u] = f; dep[u] = dep[f] + 1;
    for (const auto &v : G[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v; 
    }
}

void dfs2(int u, int tp) {
    top[u] = tp;
    if (son[u]) dfs2(son[u], tp);
    for (const auto &v : G[u]) {
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) return v;
    return u;
}
