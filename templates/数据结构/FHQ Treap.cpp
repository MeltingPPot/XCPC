#include <bits/stdc++.h>
using namespace std;

struct FhqTreap {
    struct Node {
        int left = 0, right = 0, value = 0, size = 1;
        uint32_t priority = 0;
    };
    vector<Node> tree{{}};
    int root = 0;
    mt19937 rng{chrono::steady_clock::now().time_since_epoch().count()};
    int nodeSize(int p) {
        return p ? tree[p].size : 0;
    }
    void pull(int p) {
        tree[p].size = nodeSize(tree[p].left) + nodeSize(tree[p].right) + 1;
    }
    int makeNode(int x) {
        tree.push_back({0, 0, x, 1, rng()});
        return tree.size() - 1;
    }
    void split(int p, int key, int &x, int &y) {
        if(!p)
            return void(x = y = 0);
        if(tree[p].value <= key)
            x = p, split(tree[p].right, key, tree[p].right, y), pull(p);
        else
            y = p, split(tree[p].left, key, x, tree[p].left), pull(p);
    }
    int merge(int x, int y) {
        if(!x || !y)
            return x | y;
        if(tree[x].priority < tree[y].priority)
            return tree[x].right = merge(tree[x].right, y), pull(x), x;
        return tree[y].left = merge(x, tree[y].left), pull(y), y;
    }
    void insert(int x) {
        int a, b;
        split(root, x, a, b);
        root = merge(merge(a, makeNode(x)), b);
    }
};
