#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, long long>> divisorBlocks(long long n) {
    vector<pair<long long, long long>> blocks;
    for(long long l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        blocks.push_back({l, r});
    }
    return blocks;
}
