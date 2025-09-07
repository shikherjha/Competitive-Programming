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

const int MOD = 1e9 + 7;
const int INF = 1e18;

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
    int n, m;
    cin >> n >> m;
    vi a(n), b(m);
    for(auto& x : a) cin >> x;
    for(auto& x : b) cin >> x;
    int j = 0;
    for(int i = 0; i < n && j < m; i++)
        if(a[i] >= b[j]) j++;
    if(j == m){
        cout << 0 << endl;
        return;
    }
    auto helper = [&](int k){
        int dp0 = 0;
        int dp1 = -m;
        if(m > 0 && k >= b[0]) dp1 = 1;
        for(int i = 0; i < n; i++){
            if(dp0 < m && k >= b[dp0]) {
            	dp1 = max(dp1, dp0 + 1);
            }	
            if(dp0 < m && a[i] >= b[dp0]) {
            	dp0++;
            }	
            if(dp1 < m && dp1 >= 0 && a[i] >= b[dp1]) {
            	dp1++;
            }	
        }
        if(dp0 < m && k >= b[dp0]) {
        	dp1 = max(dp1, dp0 + 1);
        }	
        return dp1 >= m;
    };
    if(!helper(INT_MAX)){
        cout << -1 << endl;
        return;
    }
    vi c = b;
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    int s = 0, e = (int)c.size() - 1, ans = -1;
    while(s <= e){
        int m = (s + e) / 2;
        if(helper(c[m])){
            ans = m;
            e = m - 1;
        } else {
            s = m + 1;
        }
    }
    cout << c[ans] << endl;
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
