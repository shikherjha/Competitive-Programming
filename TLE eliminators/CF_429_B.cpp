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

void solve() {
    int n,m; cin >> n >> m;
    vvi grid(n,vi(m));
    f(i,0,n){
        f(j,0,m){
            cin >> grid[i][j];
        }
    }

    // dp1[i][j] -> represents (0,0) to (i,j)
    // dp2[i][j] -> represents (n-1,1) to (i,j)
    // dp3[i][j] -> represents (i,j) to (n-1,m-1)
    // dp4[i][j] -> represents (i,j) to (1,m-1)

    vvi dp1(n,vi(m,0)), dp2(n,vi(m,0)), dp3(n,vi(m,0)), dp4(n,vi(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int t1=0, t2=0;
            if(i-1>=0) t1 = dp1[i-1][j];
            if(j-1>=0) t2 = dp1[i][j-1];
            dp1[i][j] = grid[i][j] + max(t1,t2);
        }
    }
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<m;j++){
            int t1=0, t2=0;
            if(i+1<n) t1 = dp2[i+1][j];
            if(j-1>=0) t2 = dp2[i][j-1];
            dp2[i][j] = grid[i][j] + max(t1,t2);
        }
    }
    for(int i=n-1;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            int t1=0, t2=0;
            if(i+1<n) t1 = dp3[i+1][j];
            if(j+1<m) t2 = dp3[i][j+1];
            dp3[i][j] = grid[i][j] + max(t1,t2);
        }
    }
    for(int i=0;i<n;i++){
        for(int j=m-1;j>=0;j--){
            int t1=0, t2=0;
            if(i-1>=0) t1 = dp4[i-1][j];
            if(j+1<m) t2 = dp4[i][j+1];
            dp4[i][j] = grid[i][j] + max(t1,t2);
        }
    }

    int ans = -INF;
    for(int i=1;i<n-1;i++){
        for(int j=1;j<m-1;j++){
            int t1 = dp1[i][j-1]+dp3[i][j+1] + dp2[i+1][j]+dp4[i-1][j];
            int t2 = dp1[i-1][j]+dp3[i+1][j] + dp2[i][j-1] + dp4[i][j+1];
            ans = max({ans,t1,t2});
        }
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

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}