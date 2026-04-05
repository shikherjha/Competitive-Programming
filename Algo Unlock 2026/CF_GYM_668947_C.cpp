#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    vector<int> a(n);
    for(auto& i:a) cin >> i;
    sort(a.rbegin(),a.rend());
    cout << a[n/2] << endl;
}