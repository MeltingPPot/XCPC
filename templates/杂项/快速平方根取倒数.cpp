#include <bits/stdc++.h>
using namespace std;

float fastInverseSqrt(float x) {
    float half = 0.5F * x, y = x;
    uint32_t bits;
    memcpy(&bits, &y, sizeof(bits));
    bits = 0x5f3759df - (bits >> 1);
    memcpy(&y, &bits, sizeof(y));
    return y * (1.5F - half * y * y);
}
