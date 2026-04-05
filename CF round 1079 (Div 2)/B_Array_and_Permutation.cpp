#include<bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vector<int> a(n), p(n);
        for(auto& i:p) cin >> i;
        for(auto& i:a) cin >> i;

        vector<int> tmp;
        tmp.push_back(a[0]);
        for(int i=1;i<n;i++){
            if(a[i]!=a[i-1]) tmp.push_back(a[i]);
        }
        // for(int x: tmp) cout << x << ' ';
        // cout << endl;
        int i=0,j=0;
        int m = tmp.size();
        while(i<m && j<n){
            if(tmp[i]==p[j]){
                i++; j++;
            }
            else j++;
        }
        if(i==m) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}