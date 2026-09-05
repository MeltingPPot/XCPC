#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int len;

struct Query {
    int l, r, id, tim;
    bool operator <(const Query &rhs) const {
        if (l / len != rhs.l / len) return l / len < rhs.l / len;
        if (r / len != rhs.r / len) return r / len < rhs.r / len;
        return tim < rhs.tim;
    }
};

struct Modify {
    int pos, val, tim;
};

void solve() {
    int n, m;
    std::cin >> n >> m;
    //qB = mn^2 / B^2 -> B = (mn^2/q)^ 1/3 
    std::vector <int> a(n + 1), ans(m + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    int qcnt = 0, mcnt = 0;
    std::vector <Query> qry;
    std::vector <Modify> mdf;
    mdf.push_back({});
    for (int i = 1; i <= m; i++) {
        std::string s;
        int x, y;
        std::cin >> s >> x >> y;
        if (s == "Q") {
            ++qcnt;
            qry.push_back({x, y, qcnt, mcnt});
        }
        else {
            ++mcnt;
            mdf.push_back({x, y, mcnt});
        }
    }
    len = -1; 
    ll mincost = 1e18;
    for (int B = 1; B <= n; B++) {
        ll cost = 1ll * qcnt * B + 1ll * n * n / B + 1ll * mcnt * n * n / B / B;
        if (cost < mincost) {
            mincost = cost;
            len = B;
        }
    }
    std::sort(qry.begin(), qry.end());
    int l = 1, r = 0, t = 0;
    std::vector <int> cnt(1000005);
    int curans = 0;

    auto add = [&](int pos) {
        if (!cnt[a[pos]]++) curans++;
    };

    auto del = [&](int pos) {
        if (!--cnt[a[pos]]) curans--;
    };

    auto modify = [&](int tim) {
        int pos = mdf[tim].pos;
        if (l <= pos && pos <= r) del(pos);
        std::swap(a[pos], mdf[tim].val);
        if (l <= pos && pos <= r) add(pos);
    };

    for (const auto &p : qry) {
        int _l = p.l, _r = p.r, _t = p.tim;
        while (t < _t) modify(++t);
        while (_t < t) modify(t--);
        while (l < _l) del(l++);
        while (_l < l) add(--l);
        while (r < _r)  add(++r);
        while (_r < r) del(r--);
        ans[p.id] = curans;
    }

    for (int i = 1; i <= qcnt; i++) {
        std::cout << ans[i] << '\n';
    }
}
