#include <bits/stdc++.h>

using ll = long long;
using pii = std::pair <int, int>;

constexpr int MAXN = 7e5 + 5;
constexpr int K = 3e6 + 5;

std::vector <pii> G[K << 1];

void add(int u, int v, int w) {
    G[u].push_back({v, w});
}

int tid[MAXN];

struct Sgt {
    struct Node {
        int l, r;
    }t[MAXN << 2];
    void build(int p, int l, int r) {
        t[p].l = l; t[p].r = r;
        if (l == r) {
            tid[l] = p;
            return;
        }
        int mid = (l + r) >> 1;
        add(p, p << 1, 0); add(p, p << 1 | 1, 0);
        add((p << 1) + K, p + K, 0); add((p << 1 | 1) + K, p + K, 0);
        build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
    }
    void connect(int p, int u, int l, int r, int w, int op) {//op=0 v->[l, r] op=1 [l,r]->v
        if (l <= t[p].l && t[p].r <= r) {
            if (op == 0) add(tid[u] + K, p, w);
            else if (op == 1) add(p + K, tid[u], w);
            return;
        }
        int mid = (t[p].l + t[p].r) >> 1;
        if (l <= mid) connect(p << 1, u, l, r, w, op);
        if (r > mid) connect(p << 1 | 1, u, l, r, w, op);
    }
}t;

void solve() {
    int n, m, s;
    std::cin >> n >> m >> s;
    t.build(1, 1, n + 2 * m);
    for (int i = 1; i <= n + 2 * m; i++) {
        add(tid[i], tid[i] + K, 0);
        add(tid[i] + K, tid[i], 0);
    }
    for (int i = 1; i <= m; i++) {
        int l1, r1, l2, r2;
        std::cin >> l1 >> r1 >> l2 >> r2;
        t.connect(1, n + 2 * i - 1, l1, r1, 1, 1);
        t.connect(1, n + 2 * i - 1, l2, r2, 0, 0);
        t.connect(1, n + 2 * i, l2, r2, 1, 1);
        t.connect(1, n + 2 * i, l1, r1, 0, 0);
        
    }
    std::vector <int> dis(K << 1);
    auto bfs = [&](int s) {
        std::fill(dis.begin(), dis.end(), 0x3f3f3f3f);
        std::deque <int> q;
        q.push_back(tid[s]); dis[tid[s]] = 0;
        while (q.size()) {
            int u = q.front(); q.pop_front();
            for (const auto &p : G[u]) {
                int v = p.first, w = p.second;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    if (w == 0) q.push_front(v);
                    else q.push_back(v);
                } 
            }
        }
    };
    bfs(s);
    for (int i = 1; i <= n; i++) std::cout << dis[tid[i]] << '\n';
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int T = 1;
    // std::cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}