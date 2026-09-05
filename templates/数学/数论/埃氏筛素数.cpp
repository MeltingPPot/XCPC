#include<bits/stdc++.h>
using namespace std;
template <int MAXN> vector<int> get_prim_bitset(){
    int cnt(0);
    static bitset<MAXN + 10> vis;
    vector<int> prim;
    vis[0] = vis[1] = 1;
    for(int i = 2; i <= MAXN; ++i){
        if(vis[i])
            continue;
        prim.emplace_back(i);
        for(long long j = 1LL * i * i; j <= MAXN; j += i)
            vis[j] = 1;
    }
    return prim;
}