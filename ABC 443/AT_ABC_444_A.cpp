#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    set<int> s;
    while(n){
        s.insert(n%10);
        n /= 10;
    }
    if(s.size()==1){
        cout << "Yes" << endl;
    }
    else cout << "No" << endl;
}