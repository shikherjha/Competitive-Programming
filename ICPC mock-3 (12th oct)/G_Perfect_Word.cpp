#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

int f(int x) {
    if(x == 0) return 1;
    if(x < 3) return x + 1; // f(1)=2, f(2)=3
    if(x % 3 == 0) return f(x/3) + 1;
    else return f(x-1) + 1;
}

void solve() {
    int l, r; 
    cin >> l >> r;
    
    // candidate chosen as before:
    int candidate = r - ((r + 1) % 3);
    
    int ans = f(r);
    if(candidate >= l) {
        ans = max(ans, f(candidate));
    }
    // Additional check: try candidate - 1 if it lies in [l,r]
    if(candidate - 1 >= l) {
        ans = max(ans, f(candidate - 1));
    }
    
    cout << ans << endl;
}

int32_t main() {
    fastio();

#ifdef LOCAL
    freopen("inputf.in", "r", stdin);
    freopen("output.in", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}