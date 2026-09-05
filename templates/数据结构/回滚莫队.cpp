#include<bits/stdc++.h>
using namespace std;

int len;

struct Query {
    int l, r, id;
    bool operator < (const Query &rhs) {
        if (l / len != rhs.l / len) return l / len < rhs.l / len;
        return r < rhs.r;
    }
};

void solve() {
    int n;
    std::cin >> n;
    std::vector <int> a(n + 1), lsh; 
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        lsh.push_back(a[i]);
    }
    std::sort(lsh.begin(), lsh.end());
    lsh.erase(std::unique(lsh.begin(), lsh.end()), lsh.end());
    for (int i = 1; i <= n; i++) {
        a[i] = std::lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
    }

    int m;
    std::cin >> m;
    std::vector <Query> qry;
    for (int i = 1; i <= m; i++) {
        int l, r;
        std::cin >> l >> r;
        qry.push_back({l, r, i});
    }
    len = sqrt(n);
    std::sort(qry.begin(), qry.end());
    std::vector <int> lpos(n + 1), rpos(n + 1), tmp(n + 1), ans(m + 1);
    int lst = -1;
    int l, r, curans;
    for (int i = 0; i < m; i++) {
        if (qry[i].l / len == qry[i].r / len) {
            for (int j = qry[i].l; j <= qry[i].r; j++) {
                if (!tmp[a[j]]) tmp[a[j]] = j;
                else ans[qry[i].id] = std::max(ans[qry[i].id], j - tmp[a[j]]);
            }
            for (int j = qry[i].l; j <= qry[i].r; j++) tmp[a[j]] = 0;
            continue;
        }
        int blk = qry[i].l / len;
        blk++;
        if (blk != lst) {
            r = len * blk - 1, l = r + 1;
            curans = 0;
            lst = blk;
            std::fill(lpos.begin(), lpos.end(), 0);
            std::fill(rpos.begin(), rpos.end(), 0);
        }
        while (r < qry[i].r) {
            ++r;
            if (!lpos[a[r]]) {
                lpos[a[r]] = rpos[a[r]] = r;
            }
            else {
                rpos[a[r]] = r;
                curans = std::max(curans, r - lpos[a[r]]);
            }
        }
        int tmp_ans = curans;
        int _l = l;
        std::vector <int> v;
        while (_l > qry[i].l) {
            --_l;
            if (!rpos[a[_l]]) {
                v.push_back(a[_l]);
                rpos[a[_l]] = _l;
            }
            else tmp_ans = std::max(tmp_ans, rpos[a[_l]] - _l); 
        }
        ans[qry[i].id] = tmp_ans;
        for (const auto &x : v) rpos[x] = 0;
    }

    for (int i = 1; i <= m; i++) {
        std::cout << ans[i] << '\n';
    }
}
