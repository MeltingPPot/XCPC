#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Dinic {
    struct Edge {
        int to, rev;
        i64 cap;
    };
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : g(n), level(n), it(n) {
    }
    void addEdge(int u, int v, i64 cap) {
        int a = g[u].size(), b = g[v].size();
        g[u].push_back({v, b, cap});
        g[v].push_back({u, a, 0});
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto e : g[u])
                if(e.cap && level[e.to] < 0)
                    q.push(e.to), level[e.to] = level[u] + 1;
        }
        return level[t] >= 0;
    }
    i64 dfs(int u, int t, i64 f) {
        if(u == t)
            return f;
        for(int &i = it[u]; i < (int)g[u].size(); ++i) {
            Edge &e = g[u][i];
            if(e.cap && level[e.to] == level[u] + 1) {
                i64 used = dfs(e.to, t, min(f, e.cap));
                if(used)
                    return e.cap -= used, g[e.to][e.rev].cap += used, used;
            }
        }
        return 0;
    }
    i64 maxFlow(int s, int t) {
        i64 ans = 0, f;
        while(bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while((f = dfs(s, t, 4e18)))
                ans += f;
        }
        return ans;
    }
};
