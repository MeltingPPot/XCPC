#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

vector<i64> dijkstra(const vector<vector<pair<int, int>>> &graph, int source) {
    const i64 inf = 4e18;
    vector<i64> dis(graph.size(), inf);
    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> pq;
    dis[source] = 0;
    pq.push({0, source});
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dis[u])
            continue;
        for(auto [v, w] : graph[u])
            if(dis[v] > d + w)
                pq.push({dis[v] = d + w, v});
    }
    return dis;
}
