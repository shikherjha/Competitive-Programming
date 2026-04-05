#include<bits/stdc++.h>
using namespace std;
#define int long long
/*
    it's a simple 2 pointer sliding window solution, we are just checking that
    adding a new element in the window is problematic or not
    from the mathematical equation |ai-aj|>=d this can be concluded that
    a problematic element will be that which lies in the range [a[j]-d,a[j]+d]
    that's what we are doing using the binary search (lower_bound), if it's problematic
    keep on removing the element from the start, as done in the while loop
*/
int32_t main(){
    int n,d; cin >> n >> d;
    vector<int> a(n);
    for(auto& i:a) cin >> i;

    int i=0;
    set<int> seen;
    int ans = 0;
    for(int j=0;j<n;j++){
        auto it = seen.lower_bound(a[j]-d+1);
        while(it!=seen.end() && *it<a[j]+d){
            seen.erase(a[i]);
            i++;
            it = seen.lower_bound(a[j]-d+1);
        }
        seen.insert(a[j]);
        ans += (j-i+1);
    }
    cout << ans << endl;
}

/*
    Just a mirror for now, will do pcd later on. need to run BYE!
*/