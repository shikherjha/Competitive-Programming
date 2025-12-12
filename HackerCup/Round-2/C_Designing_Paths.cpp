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
void bfs(int s, vi adj[], vi &vis) {
    queue<int> q;
    q.push(s);
    vis[s] = 1;
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

int val = 1;
void solve() {
    int n, k, m; cin >> n >> k >> m;
    vector<vector<int>> tram(m);
    vector<int> tmp(m);
    f(i,0,m){
        int a; cin >> a;
        tmp[i] = a;
        tram[i].resize(a);
        f(j,0,a){
            int x; cin >> x;
            tram[i][j] = x - 1;
        }
    }

    vector<vpi> occ(n);
    f(i,0,m){
        f(j,0,tmp[i]){
            occ[tram[i][j]].emplace_back(i,j);
        }
    }
    vvi nxt(m);
    f(i,0,m){
        nxt[i].resize(tmp[i] + 1);
        f(j,0,tmp[i]) nxt[i][j] = j;
    }
    function<int(int,int)> helper = [&](int r, int i)->int {
        if(i>=tmp[r]) return tmp[r];
        if(nxt[r][i]==i) return i;
        return nxt[r][i]=helper(r,nxt[r][i]);
    };

    vi dist(n, -1);
    deque<int> q;
    dist[0] = 0;
    q.push_back(0);

    while(!q.empty()) {
        int u = q.front(); q.pop_front();
        int du = dist[u];
        for(auto &it:occ[u]) {
            int r=it.first, idx = it.second;
            int s= idx +1;
            int e = min(idx+k, tmp[r]-1);
            if(s>e) continue;
            int i=helper(r, s);
            while (i<=e) {
                int v = tram[r][i];
                if(dist[v]==-1) {
                    dist[v]=du + 1;
                    q.push_back(v);
                }
                nxt[r][i]= i+1;
                i =helper(r,i+1);
            }
        }
    }

    int ans = 0;
    f(i,0,n){
        if(dist[i]==-1) ans += -1LL*(i + 1);
        else ans += 1LL*dist[i]*(i + 1);
    }

    cout << "Case #" << val++ << ": " << ans << endl;
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