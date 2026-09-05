#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200000 + 5;

struct Node {
    int b, c, w;
    long long ans;
};

struct Bit {
    int n;
    vector<long long> t;
    explicit Bit(int n = MAXN - 1) : n(n), t(n + 1) {}
    void update(int pos, long long value) {
        for(; pos <= n; pos += pos & -pos) t[pos] += value;
    }
    long long query(int pos) const {
        long long result = 0;
        for(; pos; pos -= pos & -pos) result += t[pos];
        return result;
    }
}t;

Node a[MAXN], tmp[MAXN];

void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid); cdq(mid + 1, r);
    int p1 = l, p2 = mid + 1, cur = l;
    while (p1 <= mid && p2 <= r) {
        if (a[p1].b <= a[p2].b) {
            t.update(a[p1].c, a[p1].w);
            tmp[cur++] = a[p1++];
        }
        else {
            a[p2].ans += t.query(a[p2].c);
            tmp[cur++] = a[p2++];
        }
    }
    while (p1 <= mid) {
        t.update(a[p1].c, a[p1].w);
        tmp[cur++] = a[p1++];
    }
    while (p2 <= r) {
        a[p2].ans += t.query(a[p2].c);
        tmp[cur++] = a[p2++];
    }
    for (int i = l; i <= mid; i++) t.update(a[i].c, -a[i].w);
    for (int i = l; i <= r; i++) a[i] = tmp[i];
}
