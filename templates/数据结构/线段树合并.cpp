#include<bits/stdc++.h>
using namespace std;

struct Node {
    int l, r, sum;
};

vector<Node> tr;

void pushup(int p) {
    tr[p].sum = tr[tr[p].l].sum + tr[tr[p].r].sum;
}

int merge(int a, int b, int l, int r) {
  if (!a) return b;
  if (!b) return a;
  if (l == r) {
    tr[a].sum += tr[b].sum;
    return a;
  }
  int mid = (l + r) >> 1;
  tr[a].l = merge(tr[a].l, tr[b].l, l, mid);
  tr[a].r = merge(tr[a].r, tr[b].r, mid + 1, r);
  pushup(a);
  return a;
}
