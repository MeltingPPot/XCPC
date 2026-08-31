#include <bits/stdc++.h>
using namespace std;

vector<int> dagSG(const vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> sg(n, -1);
    auto dfs = [&](auto &&self, int u) -> int {
        if(sg[u] != -1)
            return sg[u];
        vector<int> next;
        for(int v : graph[u])
            next.push_back(self(self, v));
        unordered_set<int> seen(next.begin(), next.end());
        sg[u] = 0;
        while(seen.count(sg[u]))
            ++sg[u];
        return sg[u];
    };
    for(int i = 0; i < n; ++i)
        dfs(dfs, i);
    return sg;
}
