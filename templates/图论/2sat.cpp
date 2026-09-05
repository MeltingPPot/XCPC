#include <bits/stdc++.h>

const int MAXN = 1e6 + 5;

int n, m;
std::vector <int> G[MAXN * 2];

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, xa, xb;
        std::cin >> a >> xa >> b >> xb;

        auto calc = [&](int i, int a) {
            if (a) return i + n;
            return i;
        };

        G[calc(a, xa ^ 1)].push_back(calc(b, xb));
        G[calc(b, xb ^ 1)].push_back(calc(a, xa));
    }

    int dcnt = 0, scc = 0;
    std::vector <int> dfn(2 * n + 1), low(2 * n + 1), belong(2 * n + 1);
    std::vector <bool> ins(2 * n + 1);
    std::stack <int> s;
    auto tarjan = [&](int u, auto self) -> void {
        dfn[u] = low[u] = ++dcnt;
        s.push(u); ins[u] = 1;
        for (const auto &v : G[u]) {
            if (!dfn[v]) {
                self(v, self);
                low[u] = std::min(low[u], low[v]);
            }
            else if (ins[v]) low[u] = std::min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            ++scc;
            int cur;
            do {
                cur = s.top(); s.pop(); ins[cur] = 0;
                belong[cur] = scc;
            }while (cur != u);
        }
    };
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) tarjan(i, tarjan);
    }
    for (int i = 1; i <= n; i++) {
        if (belong[i] == belong[i + n]) {
            std::cout << "IMPOSSIBLE" << '\n';
            return 0;
        } 
    }

    std::cout << "POSSIBLE" << '\n';
    for (int i = 1; i <= n; i++) {
        if (belong[i] > belong[i + n]) std::cout << 1 << " ";
        else std::cout << 0 << " ";
    }
    std::cout << '\n';
}