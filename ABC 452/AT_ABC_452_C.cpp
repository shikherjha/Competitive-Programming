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
/*
    very badd language problem, the problem overall was basic, but the language made it tough and time consuming
    overall. easier terms, we want to check for every string if it can be made spine string (that is it must be of exactly n
    length), and follow condition2, of all the ribs
    for ribs:
    A[i] -> represents the exact length of string that can be fixed at that particular rib
    B[i] -> represents, the exact index at which rib and spince intersect
    you can visualize there will be exactly n ribs, (same as the size of spine), and to make it trickier, instead
    each rib starting with index from spine, they intersect at b[i] 
    then it becomes easier, constraint allows N*M solution
    so created a valid temporary vector to store, which values intersect for quicker than the solution was simple.
*/

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i=0; i<n; i++) {
        cin >> a[i] >> b[i];
    }
    int m; cin >> m;
    vector<string> s(m);
    for(auto& i: s) cin >> i;

    vector<vector<bool>> tmp(m, vector<bool>(26, false));
    for (int i=0; i<m; i++) {
        int len = s[i].size();
        for (int j=0; j<n; j++) {
            if (len == a[j]) tmp[j][s[i][b[j]-1]-'a'] = true;
        }
    }
    for (int i=0; i<m; i++) {
        if (s[i].size() != n) {
            cout << "No" << endl;
            continue;
        }
        bool flag = true;
        for (int j=0; j<n; j++) {
            if (!tmp[j][s[i][j] - 'a']) {
                flag = false;
                break;
            }
        }
        if (flag) cout << "Yes" << endl;
        else cout << "No" << endl;
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
    // cin >> t;
    while (t--) solve();

    return 0;
}