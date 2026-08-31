#include <bits/stdc++.h>
using namespace std;

template <class F> double simpson(F f, double l, double r) {
    double m = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(m) + f(r)) / 6;
}
template <class F> double adaptiveSimpson(F f, double l, double r, double eps, double whole) {
    double m = (l + r) / 2, left = simpson(f, l, m), right = simpson(f, m, r);
    if(abs(left + right - whole) <= 15 * eps)
        return left + right + (left + right - whole) / 15;
    return adaptiveSimpson(f, l, m, eps / 2, left) + adaptiveSimpson(f, m, r, eps / 2, right);
}
