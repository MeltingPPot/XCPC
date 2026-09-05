#include<bits/stdc++.h>
using namespace std;

double sqrtNewton(double x){
    if(x < 0)
        return numeric_limits<double>::quiet_NaN();
    if(x == 0)
        return 0;
    double y = x;
    for(int i = 0; i < 100; ++i){
        double ny = (y + x / y) / 2;
        if(abs(ny - y) < 1e-12)
            return ny;
        y = ny;
    }
    return y;
}
