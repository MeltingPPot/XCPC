#include<bits/stdc++.h>
using namespace std;

template <class Check> long long binarySearchAnswer(long long left, long long right, Check check){
    while(left < right){
        long long mid = left + (right - left) / 2;
        if(check(mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
