#include<bits/stdc++.h>
using namespace std;

using ll=long long;

struct Min25Sieve{
    static constexpr ll mod=1000000007;
    ll n;
    int sq;
    vector<int> prime,id1,id2;
    vector<ll> primeSum,w,g0,g1;

    ll add(ll a,ll b){
        a+=b;
        return a>=mod?a-mod:a;
    }

    ll sub(ll a,ll b){
        a-=b;
        return a<0?a+mod:a;
    }

    ll sum1(ll x){
        x%=mod;
        return x*(x+1)%mod*((mod+1)/2)%mod;
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
        primeSum.assign(prime.size()+1,0);
        for(int i=0;i<(int)prime.size();i++){
            primeSum[i+1]=add(primeSum[i],prime[i]);
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
        g0.resize(w.size());
        g1.resize(w.size());
        for(int i=0;i<(int)w.size();i++){
            g0[i]=(w[i]-1)%mod;
            g1[i]=sub(sum1(w[i]),1);
        }
        for(int i=0;i<(int)prime.size()&&1LL*prime[i]*prime[i]<=n;i++){
            ll p=prime[i];
            for(int j=0;j<(int)w.size()&&p*p<=w[j];j++){
                int k=id(w[j]/p);
                g0[j]=sub(g0[j],sub(g0[k],i));
                g1[j]=sub(g1[j],p*sub(g1[k],primeSum[i])%mod);
            }
        }
    }

    ll primePhiSum(ll x){
        int pos=id(x);
        return sub(g1[pos],g0[pos]);
    }

    ll dfs(ll x,int from){
        if(x<2)return 0;
        ll ans=sub(primePhiSum(x),sub(primeSum[from],from));
        if(from==(int)prime.size()||prime[from]>x)return ans;
        for(int i=from;i<(int)prime.size()&&1LL*prime[i]*prime[i]<=x;i++){
            ll p=prime[i],pw=p;
            for(;pw*p<=x;pw*=p){
                ll phiPower=(pw-pw/p)%mod;
                ll nextPhi=pw%mod*(p-1)%mod;
                ans=add(ans,add(phiPower*dfs(x/pw,i+1)%mod,nextPhi));
            }
        }
        return ans;
    }

    ll sumPhi(ll value){
        init(value);
        return add(dfs(n,0),1);
    }
};
