#include <bits/stdc++.h>
using namespace std;

template <class F> double goldenSection(double left, double right, F f) {
    constexpr double ratio = (sqrt(5.0) - 1) / 2;
    double x1 = right - ratio * (right - left), x2 = left + ratio * (right - left), f1 = f(x1),
           f2 = f(x2);
    for(int i = 0; i < 100; ++i)
        if(f1 < f2)
            right = x2, x2 = x1, f2 = f1, x1 = right - ratio * (right - left), f1 = f(x1);
        else
            left = x1, x1 = x2, f1 = f2, x2 = left + ratio * (right - left), f2 = f(x2);
    return (left + right) / 2;
}
