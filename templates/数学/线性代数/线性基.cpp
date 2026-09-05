#include<bits/stdc++.h>
using namespace std;
using u64 = uint64_t;

struct LinearBasis {
    u64 b[64]{};
    bool insert(u64 x){
        for(int i = 63; i >= 0; --i)
            if(x >> i & 1){
                if(!b[i])
                    return b[i] = x, true;
                x ^= b[i];
            }
        return false;
    }
    u64 maxXor() const {
        u64 ans = 0;
        for(int i = 63; i >= 0; --i)
            ans = max(ans, ans ^ b[i]);
        return ans;
    }
};
