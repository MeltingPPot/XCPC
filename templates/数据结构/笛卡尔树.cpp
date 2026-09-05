#include<bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector <int> a(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    struct Node {
        int ls, rs;
    };
    std::vector <Node> t(n + 1);
    auto build = [&](int n, std::vector <int> &a) {
        std::stack <int> st;
        for (int i = 1; i <= n; i++) {
            int lst = 0;
            while (st.size() && a[i] < a[st.top()]) {
                lst = st.top(); 
                st.pop();
            } 
            if (st.size()) t[st.top()].rs = i;
            t[i].ls = lst;
            st.push(i);
        }
    };

    build(n, a);
    ll ansl = 0, ansr = 0;
    for (int i = 1; i <= n; i++) {
        ansl ^= (1ll * i * (t[i].ls + 1));
        ansr ^= (1ll * i * (t[i].rs + 1));
    }

    std::cout << ansl << " " << ansr << '\n';
}
