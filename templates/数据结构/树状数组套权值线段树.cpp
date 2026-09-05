#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 200000 + 5;
constexpr int MAXV = 1000000000;

struct Sgt {
    struct Node {
        int ls, rs, cnt;
    }t[MAXN * 605];
    int tot = 0;
    void pushup(int p) {
        t[p].cnt = t[t[p].ls].cnt + t[t[p].rs].cnt;
    }
    void insert(int &p, int l, int r, int pos, int delta) {
        if (!p) p = ++tot;
        if (l == r) {
            t[p].cnt += delta;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) insert(t[p].ls, l, mid, pos, delta);
        else insert(t[p].rs, mid + 1, r, pos, delta);
        pushup(p);
    }
}t;

struct Bit {
    #define lowbit(x) ((x) & (-(x)))
    int rt[MAXN];
    void update(int pos, int v, int delta) {
        for (; pos < MAXN; pos += lowbit(pos)) t.insert(rt[pos], 0, MAXV, v, delta);
    }
    int query(int l, int r, int k) {
        l--;
        std::vector <int> vl, vr;
        for (; l; l -= lowbit(l)) vl.push_back(rt[l]);
        for (; r; r -= lowbit(r)) vr.push_back(rt[r]);
        int L = 0, R = MAXV;
        while (L != R) {
            int cnt = 0, mid = (L + R) >> 1;
            for (const auto &x : vr) {
                cnt += t.t[t.t[x].ls].cnt;
            }
            for (const auto &x : vl) {
                cnt -= t.t[t.t[x].ls].cnt;
            }
            if (k <= cnt) {
                R = mid;
                for (auto &x : vr) x = t.t[x].ls;
                for (auto &x : vl) x = t.t[x].ls;
            }
            else {
                L = mid + 1;
                k -= cnt;
                for (auto &x : vr) x = t.t[x].rs;
                for (auto &x : vl) x = t.t[x].rs;
            }
        }
        return L;
    }
}bit;
