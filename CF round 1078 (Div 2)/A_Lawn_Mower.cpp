#include<bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while(t--){
        int n,w; cin >> n >> w;
        if(w==1) cout << 0 << endl;
        else{
            cout << (n/w)*(w-1) + (n%w) << endl;
        }
    }
}