#include <bits/stdc++.h>
using namespace std;
vector<int> get_min_prime(int MAXN) {
    vector<int> vis(MAXN + 10), prim;
    for(int i = 2; i <= MAXN; ++i) {
        if(!vis[i])
            prim.emplace_back(i);
        for(int j = 0; j < (int)prim.size() && prim[j] <= MAXN / i; ++j) {
            vis[prim[j] * i] = 1;
            if(i % prim[j] == 0)
                break;
        }
    }
    return prim;
}
vector<int> get_prim(int MAXN) {
    vector<int> vis(MAXN + 10), prim;
    for(int i = 2; i <= MAXN; ++i) {
        if(!vis[i])
            prim.emplace_back(i), vis[i] = i;
        for(int j = 0; j < (int)prim.size() && prim[j] <= MAXN / i; ++j) {
            vis[prim[j] * i] = prim[j];
            if(i % prim[j] == 0)
                break;
        }
    }
    return prim;
}
