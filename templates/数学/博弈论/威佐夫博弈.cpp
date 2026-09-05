#include<bits/stdc++.h>
using namespace std;

bool wythoffLosing(long long a, long long b){
    if(a > b)
        swap(a, b);
    long long k = b - a;
    return a == (long long)(k * ((sqrtl(5) + 1) / 2));
}
