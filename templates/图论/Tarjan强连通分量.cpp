#include <bits/stdc++.h>
using namespace std;

struct TarjanSCC {
    vector<vector<int>> graph;
    vector<int> dfn, low, component, stack;
    vector<bool> inStack;
    int timer = 0, count = 0;
    TarjanSCC(vector<vector<int>> graph)
        : graph(move(graph)), dfn(this->graph.size()), low(this->graph.size()),
          component(this->graph.size(), -1), inStack(this->graph.size()) {
    }
    void dfs(int u) {
        dfn[u] = low[u] = ++timer;
        stack.push_back(u);
        inStack[u] = true;
        for(int v : graph[u])
            if(!dfn[v])
                dfs(v), low[u] = min(low[u], low[v]);
            else if(inStack[v])
                low[u] = min(low[u], dfn[v]);
        if(dfn[u] == low[u]) {
            while(true) {
                int v = stack.back();
                stack.pop_back();
                inStack[v] = false;
                component[v] = count;
                if(v == u)
                    break;
            }
            ++count;
        }
    }
    void solve() {
        for(int i = 0; i < (int)graph.size(); ++i)
            if(!dfn[i])
                dfs(i);
    }
};
