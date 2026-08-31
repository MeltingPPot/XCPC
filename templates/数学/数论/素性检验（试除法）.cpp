#include <bits/stdc++.h>
using namespace std;

bool isPrime(long long n) {
    if(n < 2)
        return false;
    if(n % 2 == 0)
        return n == 2;
    for(long long d = 3; d <= n / d; d += 2)
        if(n % d == 0)
            return false;
    return true;
}
