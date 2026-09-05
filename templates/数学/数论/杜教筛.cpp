#include<bits/stdc++.h>
using namespace std;

using ll=long long;

struct DuJiaoSieve{
    int limit;
    vector<int> prime,mu;
    vector<ll> phi,preMu,prePhi;
    vector<bool> vis;
    unordered_map<ll,ll> memoMu,memoPhi;

    void init(int n){
        limit=n;
        prime.clear();
        mu.assign(limit+1,0);
        phi.assign(limit+1,0);
        preMu.assign(limit+1,0);
        prePhi.assign(limit+1,0);
        vis.assign(limit+1,false);
        mu[1]=1;
        phi[1]=1;
        for(int i=2;i<=limit;i++){
            if(!vis[i]){
                prime.push_back(i);
                mu[i]=-1;
                phi[i]=i-1;
            }
            for(int p:prime){
                if(1LL*i*p>limit)break;
                vis[i*p]=true;
                if(i%p==0){
                    mu[i*p]=0;
                    phi[i*p]=phi[i]*p;
                    break;
                }
                mu[i*p]=-mu[i];
                phi[i*p]=phi[i]*(p-1);
            }
        }
        for(int i=1;i<=limit;i++){
            preMu[i]=preMu[i-1]+mu[i];
            prePhi[i]=prePhi[i-1]+phi[i];
        }
        memoMu.clear();
        memoPhi.clear();
    }

    ll sumMu(ll n){
        if(n<=limit)return preMu[n];
        if(memoMu.count(n))return memoMu[n];
        ll ans=1;
        for(ll l=2,r;l<=n;l=r+1){
            r=n/(n/l);
            ans-=(r-l+1)*sumMu(n/l);
        }
        return memoMu[n]=ans;
    }

    ll sumPhi(ll n){
        if(n<=limit)return prePhi[n];
        if(memoPhi.count(n))return memoPhi[n];
        ll ans=(ll)((__int128)n*(n+1)/2);
        for(ll l=2,r;l<=n;l=r+1){
            r=n/(n/l);
            ans-=(r-l+1)*sumPhi(n/l);
        }
        return memoPhi[n]=ans;
    }
};
