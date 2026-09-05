#include<bits/stdc++.h>
using namespace std;

template <class F> int memoizedDfs(int state, vector<int> &memo, F transition){
    if(memo[state] != -1)
        return memo[state];
    return memo[state] = transition(state);
}
