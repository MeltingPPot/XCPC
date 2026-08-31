#include <bits/stdc++.h>
using namespace std;
int sqrt_phi(int n) {
    int ans(n);
    for(int i = 2; i * i <= n; ++i) {
        if(n % i)
            continue;
        ans = ans / i * (i - 1);
        for(; n % i == 0; n /= i)
            ;
    }
    if(n > 1)
        ans = ans / n * (n - 1);
    return ans;
} // sqrt
vector<int> euler_phi(int MAXN) {
    vector<int> phi(MAXN + 10), prim;
    phi[1] = 1;
    for(int i = 2; i <= MAXN; ++i) {
        if(!phi[i])
            prim.emplace_back(i), phi[i] = i - 1;
        for(int j = 0; j < (int)prim.size() && prim[j] <= MAXN / i; ++j) {
            if(!(i % prim[j])) {
                phi[i * prim[j]] = prim[j] * phi[i];
                break;
            }
            phi[i * prim[j]] = (prim[j] - 1) * phi[i];
        }
    }
    return phi;
}
