#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int,int>
#define vpi vector<pii>
#define f(i,a,b) for(int i=a; i<b; i++)
#define rf(i,a,b) for(int i=a; i>=b; i--)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define endl '\n'

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

#ifdef LOCAL
#define dbg(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
#define dbg(x)
#endif

template<class T> void _print(T x) { cerr << x; }
template<class T, class V> void _print(pair<T,V> p) { cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}"; }
template<class T> void _print(vector<T> v) { cerr << "["; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }

const int MOD = 1000000007;
const int INF = 1000000000000000000LL;

int mod_add(int a, int b) { return (a % MOD + b % MOD) % MOD; }
int mod_sub(int a, int b) { return (a % MOD - b % MOD + MOD) % MOD; }
int mod_mul(int a, int b) { return (a % MOD * b % MOD) % MOD; }
int mod_pow(int a, int b) {
    int res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = mod_mul(res, a);
        a = mod_mul(a, a);
        b >>= 1;
    }
    return res;
}
int mod_inv(int a) { return mod_pow(a, MOD - 2); }

struct DSU {
    vi parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        f(i, 0, n) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false;
        if (rank[xr] < rank[yr]) swap(xr, yr);
        parent[yr] = xr;
        if (rank[xr] == rank[yr]) rank[xr]++;
        return true;
    }
};

void dfs(int node, vi adj[], vi &vis) {
    vis[node] = 1;
    for (int child : adj[node]) {
        if (!vis[child]) dfs(child, adj, vis);
    }
}
void bfs(int start, vi adj[], vi &vis) {
    queue<int> q;
    q.push(start);
    vis[start] = 1;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int child : adj[node]) {
            if (!vis[child]) {
                vis[child] = 1;
                q.push(child);
            }
        }
    }
}

vi sieve(int n) {
    vi isPrime(n+1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i*i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i*i; j <= n; j += i) isPrime[j] = 0;
        }
    }
    return isPrime;
}
int pow_2(int n){
    int cnt = 0;
    while(n%2==0){
        cnt++;
        n/=2;
    }
    return cnt;
}
int pow_5(int n){
    int cnt = 0;
    while(n%5==0){
        cnt++;
        n/=5;
    }
    return cnt;
}
bool helper(int mid, int m, int c1, int c2){
    
    int rem1 = max((int)0,mid-c1), rem2 = max((int)0,mid-c2);
    int x =1;
    f(i,0,rem1){
        
        if(x>m) return false;
        x*=2;
    }
    f(i,0,rem2){
        
        if(x>m) return false;
        x*=5;
    }
    return x<=m;

}

void solve() {
    int n,m; cin >> n >>m;
    int c1,c2,c3,c4;
    c1 = pow_2(n);
    c2 = pow_5(n);
    //cout << c1 << ' ' << c2 << endl;
    int s =0, e=60;
    int trail_0 = 0;
    while(s<=e){
        int mid = (e-s)/2 + s;
        if(helper(mid,m,c1,c2)){
            s = mid+1;
            trail_0 = mid;
        }
        else{
            e = mid-1;
        }
    }
    //cout << trail_0 << endl;
    if(trail_0==0){
        cout << n*m << endl;
        return;
    }
    else{
        int rem2 = max((int)0,trail_0-c1);
        int rem5 = max((int)0,trail_0-c2);

        int ans = 1;
        f(i,0,rem2){
            
            if(ans>m) break;
            ans *= 2;
        }
        f(i,0,rem5){
            
            if(ans>m) break;
            ans *= 5;
        }
        int mul = m/ans;
        ans *= (mul*n);

        cout << ans << endl;
    }



    



}

int32_t main() {
    fastio();

#ifdef LOCAL
    freopen("inputf.in", "r", stdin);
    freopen("output.in", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}