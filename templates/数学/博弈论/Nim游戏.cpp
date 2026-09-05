#include<bits/stdc++.h>
using namespace std;

bool nimWinning(const vector<int> &piles){
    int x = 0;
    for(int pile : piles)
        x ^= pile;
    return x != 0;
}
