#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Flow {
    static constexpr int INF = 0x7f7f7f7f;
    int n;
    struct Edge {
        int to, w, rev, c;
    };
    std::vector <std::vector<Edge> > G;
    std::vector <int> dep, cur, dis, inq;
    Flow(int _n = 0) : n(_n) {
        G.resize(n + 1);
        dep.resize(n + 1);
        cur.resize(n + 1);
        dis.resize(n + 1);
        inq.resize(n + 1);
    }
    void clear(int _n) {
        for (int i = 0; i <= n; i++) G[i].clear();
        G.clear(); G.resize(_n + 1);
        dep.clear(); dep.resize(_n + 1, 0);
        cur.clear(); cur.resize(_n + 1, 0);
        dis.clear(); dis.resize(_n + 1, 0);
        inq.clear(); inq.resize(_n + 1, 0);
        n = _n;
    }
    void add(int u, int v, int w, int c) {
        int a = G[u].size(), b = G[v].size();
        G[u].push_back({v, w, b, c});
        G[v].push_back({u, 0, a, -c});
    }
    bool SPFA(int s, int t) {
        for (int i = 0; i <= n; i++) {
            dep[i] = 0;
            cur[i] = 0;
            inq[i] = 0;
            dis[i] = INF;
        }
        std::queue <int> q;
        q.push(s); dep[s] = 1; inq[s] = 1; dis[s] = 0;
        while(q.size()) {
            int u = q.front(); q.pop(); inq[u] = 0;
            for (const auto &[v, w, id, c] : G[u]) {
                if (w && dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    dep[v] = dep[u] + 1;
                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = 1; 
                    }    
                }
            }
        }
        return (dep[t] != 0); 
    }
    ll mincost = 0;
    int dfs(int u, int t, int flow) {
        if (u == t) return flow;
        int rest = flow;
        for (int i = cur[u]; i < G[u].size(); i++) {
            const auto &[v, w, rev, c] = G[u][i];
            if (!w || dep[v] != dep[u] + 1 || dis[v] != dis[u] + c) continue;
            int used = dfs(v, t, std::min(w, rest));
            rest -= used;
            G[u][i].w -= used; G[v][rev].w += used;
            mincost += 1ll * c * used;
            cur[u] = i;
            if (!rest) return flow;  
        }
        return flow - rest;
    }
    std::pair<ll, ll> MCMF(int s, int t) {
        ll ret = 0;
        while (SPFA(s, t)) {
            int flow;
            while ((flow = dfs(s, t, INF))) ret += flow;
        }
        return std::make_pair(ret, mincost);
    }
};
