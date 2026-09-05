#include<bits/stdc++.h>
using namespace std;

int mex(const vector<int> &values){
    unordered_set<int> seen(values.begin(), values.end());
    for(int x = 0;; ++x)
        if(!seen.count(x))
            return x;
}
