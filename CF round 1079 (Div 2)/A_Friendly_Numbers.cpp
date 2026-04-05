#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int x; cin >> x;
        auto helper = [&](int n) -> int{
            int sum = 0;
            while(n){
                sum += n%10;
                n /= 10;
            }
            return sum;
        };
        int ans = 0;
        for(int i=x; i<=x+82; i++){
            if(i-helper(i)==x) ans++;
        }
        cout << ans << endl;
    }
}