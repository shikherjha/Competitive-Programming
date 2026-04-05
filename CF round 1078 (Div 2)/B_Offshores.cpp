#include<bits/stdc++.h>
using namespace std;
#define int long long
int32_t main(){
    int t; cin >> t;
    while(t--){
        int n,x,y; cin >> n >> x >> y;
        vector<int> a(n);
        for(auto& i:a) cin >> i;
        int ans = INT_MIN; int sum = 0;
        for(int i=0;i<n;i++) sum += (a[i]/x)*y;
        for(int i=0;i<n;i++){
            int tmp = sum - (a[i]/x)*y + a[i];
            ans = max(ans,tmp);
        }
        cout << ans << endl;

    }
}