#include<bits/stdc++.h>
using namespace std;

template <class F, class DF> double newton(double x, F f, DF df){
    for(int i = 0; i < 100; ++i){
        double nx = x - f(x) / df(x);
        if(abs(nx - x) < 1e-12)
            return nx;
        x = nx;
    }
    return x;
}
