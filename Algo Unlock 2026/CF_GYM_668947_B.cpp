#include<bits/stdc++.h>
using namespace std;
#define int long long
int32_t main(){
    int n; cin >> n;
    vector<int> a(n);
    int ans = 0;
    for(auto& i:a){
        cin >> i;
        ans ^= i;
    }
    cout << ans << endl;

}