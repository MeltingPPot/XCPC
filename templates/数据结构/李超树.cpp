#include<bits/stdc++.h>
using namespace std;

constexpr int MAXN = 1e5 + 5;
constexpr int MAXV = 40000;

using ll = long long;
using pii = std::pair <int, int>;
#define y1 y114514
#define y2 y114515

struct Seg {
    int x0, x1, y0, y1;
    double calc(int x) {
        if (!(x0 <= x && x <= x1)) return 0.0;
        if (x0 == x1) return std::max(y0, y1);
        double k = 1.0 * (y1 - y0) / (x1 - x0), b = 1.0 * y0 - k * x0;
        return k * x + b;
    };
}s[MAXN];

constexpr double eps = 1e-9;
int cmp(double x, double y) {
    if (x - eps > y) return 1;
    if (x + eps < y) return -1;
    return 0;
}

struct Sgt {
    struct Node {
        int l, r;
        int sid;
    }t[MAXV << 2];
    void build(int p, int l, int r) {
        t[p].l = l; t[p].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
    }
    void update(int p, int sid) {
        if (t[p].sid == 0) {
            t[p].sid = sid;
            return;
        }
        int mid = (t[p].l + t[p].r) >> 1;
        int cmid = cmp(s[t[p].sid].calc(mid), s[sid].calc(mid));
        if (cmid == -1 || (cmid == 0 && t[p].sid > sid)) std::swap(t[p].sid, sid);
        int cl = cmp(s[t[p].sid].calc(t[p].l), s[sid].calc(t[p].l)), cr = cmp(s[t[p].sid].calc(t[p].r), s[sid].calc(t[p].r));
        if (cl == -1 || (cl == 0 && t[p].sid > sid)) update(p << 1, sid);
        if (cr == -1 || (cr == 0 && t[p].sid > sid)) update(p << 1 | 1, sid);
    }
    void insert(int p, int sid) {
        if (s[sid].x0 <= t[p].l && t[p].r <= s[sid].x1) {
            update(p, sid);
            return;
        } 
        int mid = (t[p].l + t[p].r) >> 1;
        if (s[sid].x0 <= mid) insert(p << 1, sid);
        if (s[sid].x1 > mid) insert(p << 1 | 1, sid);
    }
    int query(int p, int pos) {
        if (t[p].l == t[p].r) return t[p].sid;
        int mid = (t[p].l + t[p].r) >> 1, cur = t[p].sid;
        if (pos <= mid) {
            int lid = query(p << 1, pos), cl = cmp(s[lid].calc(pos), s[cur].calc(pos));
            if (cl == 1 || (cl == 0 && lid < cur)) cur = lid;
        }
        else {
            int rid = query(p << 1 | 1, pos), cr = cmp(s[rid].calc(pos), s[cur].calc(pos));
            if (cr == 1 || (cr == 0 && rid < cur)) cur = rid;
        }
        return cur;
    }
}t;

void solve() {
    t.build(1, 1, MAXV);
    int n;
    std::cin >> n;
    int lst = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int x;
            std::cin >> x;
            x = (x + lst - 1) % 39989 + 1;
            std::cout << (lst = t.query(1, x)) << '\n';
        }
        else {
            ++cnt;
            std::cin >> s[cnt].x0 >> s[cnt].y0 >> s[cnt].x1 >> s[cnt].y1;
            s[cnt].x0 = (s[cnt].x0 + lst - 1) % 39989 + 1;
            s[cnt].x1 = (s[cnt].x1 + lst - 1) % 39989 + 1;
            s[cnt].y0 = (s[cnt].y0 + lst - 1) % 1000000000 + 1;
            s[cnt].y1 = (s[cnt].y1 + lst - 1) % 1000000000 + 1;
            if (s[cnt].x0 > s[cnt].x1) {
                std::swap(s[cnt].x0, s[cnt].x1);
                std::swap(s[cnt].y0, s[cnt].y1);
            }
            t.insert(1, cnt);
        }
    } 
}
