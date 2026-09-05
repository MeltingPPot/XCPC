#include<bits/stdc++.h>
using namespace std;

using ll=long long;

struct ZhouGeSieve{
    static constexpr ll mod=1000000007;
    ll n;
    int sq;
    vector<int> prime,id1,id2;
    vector<ll> w,primeCount;

    ll add(ll a,ll b){
        a+=b;
        return a>=mod?a-mod:a;
    }

    ll sub(ll a,ll b){
        a-=b;
        return a<0?a+mod:a;
    }

    void sieve(int n){
        vector<bool> vis(n+1,false);
        for(int i=2;i<=n;i++){
            if(!vis[i])prime.push_back(i);
            for(int p:prime){
                if(1LL*i*p>n)break;
                vis[i*p]=true;
                if(i%p==0)break;
            }
        }
    }

    int id(ll x){
        return x<=sq?id1[x]:id2[n/x];
    }

    void init(ll value){
        n=value;
        sq=sqrtl(n);
        while(1LL*(sq+1)*(sq+1)<=n)sq++;
        while(1LL*sq*sq>n)sq--;
        prime.clear();
        sieve(sq);
        id1.assign(sq+1,0);
        id2.assign(sq+1,0);
        w.clear();
        for(ll l=1,r;l<=n;l=r+1){
            r=n/(n/l);
            ll x=n/l;
            int now=w.size();
            w.push_back(x);
            if(x<=sq)id1[x]=now;
            else id2[n/x]=now;
        }
        primeCount.resize(w.size());
        for(int i=0;i<(int)w.size();i++)primeCount[i]=(w[i]-1)%mod;
        for(int i=0;i<(int)prime.size()&&1LL*prime[i]*prime[i]<=n;i++){
            ll p=prime[i];
            for(int j=0;j<(int)w.size()&&p*p<=w[j];j++){
                primeCount[j]=sub(primeCount[j],sub(primeCount[id(w[j]/p)],i));
            }
        }
    }

    ll dfs(ll x,int from){
        if(x<2)return 0;
        ll ans=2*sub(primeCount[id(x)],from)%mod;
        if(from==(int)prime.size()||prime[from]>x)return ans;
        for(int i=from;i<(int)prime.size()&&1LL*prime[i]*prime[i]<=x;i++){
            ll p=prime[i],pw=p;
            for(int e=1;pw*p<=x;e++,pw*=p){
                ans=add(ans,add((e+1)*dfs(x/pw,i+1)%mod,e+2));
            }
        }
        return ans;
    }

    //返回\sum_{i=1}^n d(i)，d(i)为约数个数函数。
    ll sumDivisorCount(ll value){
        init(value);
        return add(dfs(n,0),1);
    }
};
