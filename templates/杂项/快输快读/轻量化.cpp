#include <bits/stdc++.h>
using namespace std;
template <class T> T read() {
    T f(1), x(0);
    int ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    }
    return f * x;
}
template <class T> void write(T x) {
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}