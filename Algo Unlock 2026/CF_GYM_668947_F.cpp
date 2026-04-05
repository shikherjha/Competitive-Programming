#include<bits/stdc++.h>
using namespace std;
#define int long long
int32_t main(){
    int n; cin >> n;
    vector<int> a(n);
    for(auto& i:a) cin >> i;
    for(int i=1;i<n;i++) a[i] += a[i-1];
    for(int i=1;i<n;i++) a[i] += a[i-1];

    for(int x: a) cout << x << ' ';
    cout << endl;
}