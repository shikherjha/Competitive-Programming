#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k; cin >> n >> k;
    int ans = 0;
    for(int i=1;i<=n;i++){
        int tmp = i; int sum = 0;
        while(tmp){
            sum += tmp%10;
            tmp /= 10;
        }
        if(sum==k) ans++;
    }
    cout << ans << endl;
}