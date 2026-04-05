#include<bits/stdc++.h>
using namespace std;
//#define int long long 
int main(){
    int a,k; cin >> a >> k;
    int cnt = 0;
    //if(k<a) swap(k,a);
    if(a==k){
        cout << 0 << endl;
    }
    else if(a==1){
        cout << -1 << endl;
    }
    else{
        int power = 1;
        while(power*a<=k){
            cnt++;
            power*=a;
        }
        if(power+a>=k) cout << cnt-1 << endl;
        else cout << -1 << endl;
    }
}