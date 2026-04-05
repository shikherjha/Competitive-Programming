#include<bits/stdc++.h>
using namespace std;
/*
    I found this problem to be harder than d and e, (lol) the intuition is important, only 2 cases
    for L is possible that is the greatest element and the sum of greatest and the smallest 
    element. I had trouble handling the helper function, it's fairly simple 2 pointer approach
    was distracted and fucked implementation in the earlier phase
*/
int main(){
    int n; cin >> n;
    vector<int> a(n);
    for(auto& i:a) cin >> i;
    sort(a.begin(),a.end());
    // case-1 greatest ai is the L
    
    auto helper = [&](int l)->bool{
        int i = 0, j = n-1;
        while(i<=j){
            if(a[j]==l) j--;
            else if(a[j]>l) return false;
            else{
                if(i==j) return false;
                if(a[i]+a[j]==l){
                    i++; j--;
                }
                else return false;
            }
        }
        return true;
    };
    set<int> ans;
    if(helper(a[n-1])) ans.insert(a[n-1]);
    if(helper(a[0]+a[n-1])) ans.insert(a[n-1]+a[0]);
    for(int x: ans) cout << x << ' ';
    cout << endl;

}