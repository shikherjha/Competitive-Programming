#include<bits/stdc++.h>
using namespace std;

int main(){
    int l,r; cin >> l >> r;
    if(__builtin_clz(l)!=__builtin_clz(r)) cout << "YES" << endl;
    else cout << "NO" << endl;
}