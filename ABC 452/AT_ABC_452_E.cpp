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

const int MOD = 998244353;
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
/*
    brute: 2 loops inefficient
    ∑
N
​
  
j=1
∑
M
​
 A 
i
​
 ⋅B 
j
​
 ⋅(imodj).
    I believe somewhat we have to rearrange the equation there must be something
    something (i % j), it's the remainder, mod can rewritten as i % j = i - j*x
    where x would be quotient (floor(i/j)), so basically i % j = i - j * (i/j)
    we can take b[j] out and rearrange the summation 
    sum (b[j]) * sum (a[i]* (i-j*(i/j)))
    sum (b[j]) * (sum (a[i]*i) - j*sum(a[i]*(i/j)) 
    a[i]*i can be precomputed, by prefix sum we can calculate a[i] as well
    now the tricky part remains sum(a[i]*(i/j))
    we don't want to iterate to all j, one thing can be observed, value of i/j remains same for
    chunks, and then increment by 1 for a constant j
    i = 10, j = 3
    for i = 1,2 -> 0
    for i= 3,4,5 -> 1
    for i=6,7,8 -> 2
    for i = 9,10 -> 3
    I believe we can make chunks, and group it based on the chunk values
    for 1 -> 1 * (a3 + a4 + a5)
    for 2 -> 2* (a6 + a7 + a8)
    does these chunks won't cause TLE????
    don't think so, we are basically counting jumps of some sort
    for j = 1 -> n/1 jumps
    for j =2 -> n/2 jumps
    and so on/
    something like n * (1 + 1/2 + .... 1/m)
    this would be somewhat n*log(m)
    this can work
*/

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n+1), b(m+1);
    for (int i=1; i<=n; i++) cin >> a[i];
    for (int j=1; j<=m; j++) cin >> b[j];

    vector<int> prefA(n+1,0);
    int total_sum = 0;
    for (int i = 1; i<=n; i++) {
        prefA[i] = (prefA[i-1] + a[i]) % MOD;
        total_sum = (total_sum + a[i]*i) % MOD;
    }
    int ans = 0;
    for (int j=1; j<=m; j++) {
        int sum = 0; // represents  sum(a[i]*(i/j))
        for (int i=1; i*j<=n; i++) {
            // chunk value, goes from 0 to less than n/j
            int start = i*j, end = min(n, (i+1)*j - 1);
            int sum1 = mod_sub(prefA[end] , prefA[start-1]); // calculation for each chunks
            sum = (sum + mod_mul(i,sum1)) % MOD;
        }
        int tot = mod_sub(total_sum, mod_mul(j,sum));
        ans = mod_add(ans, mod_mul(b[j],tot));
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