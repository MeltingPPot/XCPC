#include<bits/stdc++.h>
using namespace std;
vector<int> euler_mu(int MAXN){
    vector<int> mu(MAXN + 1), prime;
    vector<bool> composite(MAXN + 1);
    if(MAXN >= 1)
        mu[1] = 1;
    for(int i = 2; i <= MAXN; ++i){
        if(!composite[i])
            prime.emplace_back(i), mu[i] = -1;
        for(int p : prime){
            if(p > MAXN / i)
                break;
            composite[i * p] = true;
            if(i % p == 0){
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}
