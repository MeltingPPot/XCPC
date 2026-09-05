#include <bits/stdc++.h>

const int MAXN = 5005;
const int MAXM = 2e5 + 5;

struct Dsu {
    int fa[MAXN];
    void init(int n) {
        for (int i = 1; i <= n; i++) fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
}dsu;

int n, m;

struct Edge {
    int u, v, w;
}E[MAXM];

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> n >> m;
    for (int i = 1;i <= m; i++) {
        std::cin >> E[i].u >> E[i].v >> E[i].w;
    }

    #define ll long long
    auto boruvka = [&]() {
        ll ans = 0;
        dsu.init(n);
        std::vector <bool> vis(m + 1);
        int ecnt = 0;
        while (1) {
            bool flag = 0;
            std::vector <int> mn(n + 1, 0x3f3f3f3f), id(n + 1, 0);
            for (int i = 1; i <= m; i++) {
                if (vis[i]) continue;
                int u = E[i].u, v = E[i].v, w = E[i].w;
                int x = dsu.find(u), y = dsu.find(v);
                if (x == y) continue;
                flag = 1;
                if (w < mn[x]) {
                    mn[x] = w;
                    id[x] = i;
                }
                if (w < mn[y]) {
                    mn[y] = w;
                    id[y] = i;
                }
            }
            if (!flag || ecnt == n - 1) break;
            for (int i = 1; i <= n; i++) {
                int x = dsu.find(i);
                if (!id[x] || vis[id[x]]) continue;
                int u = E[id[x]].u, v = E[id[x]].v;
                int X = dsu.find(u), Y = dsu.find(v);
                if (X == Y) continue;
                ++ecnt;
                ans += E[id[x]].w;
                dsu.fa[X] = Y;
                vis[id[x]] = 1;
            }
        }
        if (ecnt < n - 1) return -1ll;
        return ans;
    };

    ll ret = boruvka();
    if (ret == -1) std::cout << "orz" << '\n';
    else std::cout << boruvka() << '\n';
}