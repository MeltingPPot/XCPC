#include <bits/stdc++.h>
using namespace std;

long long gcdll(long long a, long long b) {
    a = abs(a);
    b = abs(b);
    while(b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}
