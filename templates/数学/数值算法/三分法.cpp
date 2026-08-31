#include <bits/stdc++.h>
using namespace std;

template <class F> double ternarySearch(double left, double right, F f) {
    for(int step = 0; step < 100; ++step) {
        double m1 = (2 * left + right) / 3, m2 = (left + 2 * right) / 3;
        if(f(m1) < f(m2))
            right = m2;
        else
            left = m1;
    }
    return (left + right) / 2;
}
