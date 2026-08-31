#include <bits/stdc++.h>
using namespace std;

long long fibonacciNimMove(long long n) {
    vector<long long> fib = {1, 2};
    while(fib.back() <= n - fib[fib.size() - 2])
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    long long answer = 0;
    for(auto it = fib.rbegin(); it != fib.rend(); ++it)
        if(*it <= n) {
            n -= *it;
            answer = *it;
        }
    return answer;
}
