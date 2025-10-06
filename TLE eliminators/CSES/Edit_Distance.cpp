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
    string s, t;
    cin >> s;
    cin >> t;
    int n = sz(s), m = sz(t);
    // dp[i][j] -> represents minimum edit distance between i characters of s and j characters of t
    vvi dp(n+1,vi(m+1));
    //  Base case
    f(i,0,n+1){
        dp[i][0] = i;
    }
    f(i,0,m+1){
        dp[0][i] = i;
    }

    // Transitions
     // if(s[i]==s[j])  dp[i][j] = dp[i-1][j-1]
     // else 1-> Replace the last element is either string dp[i][j] = 1 + dp[i-1][j-1]
        // 2-> Remove the last element in s dp[i][j] = 1 + dp[i-1][j]
        // 3-> Remove the last element in  t dp[i][j] = 1 + dp[i][j-1]

    f(i,1,n+1){
        f(j,1,m+1){
            char x = s[i-1];
            char y = t[j-1];
            if(x==y){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                int t1=0,t2=0,t3=0;
                if(i-1>=0 && j-1>=0)  t1 =  1 + dp[i-1][j-1];
                if(j-1>=0)  t2 = 1 + dp[i][j-1];
                if(i-1>=0)  t3 = 1 + dp[i-1][j];
                
                dp[i][j] = min({t1,t2,t3});
            }
        }
    }
    /*f(i,0,n){
        f(j,0,m){
            cout << dp[i][j] << ' ';
        }
        cout << endl;
    }*/
    cout << dp[n][m] << endl;



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