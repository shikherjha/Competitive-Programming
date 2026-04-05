#include<bits/stdc++.h> 
using namespace std;
#define int long long

/*
    a very straight forward problem, just use an array for summation, as the size is very large
    the intuition comes from the concept of difference array, basic prefix sum and carry handling
    that's the only crux of this problem
*/

int32_t main(){
    int n; cin >> n;
    vector<int> a(n);
    int maxi = INT_MIN;
    for(auto& i:a) {
        cin >> i;
        maxi = max(maxi,i);
    }
    vector<int> ans(maxi,0);
    for(int x:a){
        ans[maxi-x]++;
    }
    for(int i=1;i<maxi;i++) ans[i] += ans[i-1];
    int carry = 0;
    for(int i=maxi-1;i>=0;i--){
        if(ans[i]+carry>9){
            int sum = ans[i]+carry;
            ans[i] = sum%10;
            carry = sum/=10;
        }
        else{
            ans[i] += carry;
            carry = 0;
        }
    }
    if(carry) cout << carry;
    for(int x: ans) cout << x;
    cout << endl;
    
}