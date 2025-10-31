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
    int n,k,x; cin >> n >> k >> x;
    vi a(n);
    f(i,0,n) cin >> a[i];
    sort(all(a));
    vi pos;
    auto helper = [&](int m) -> bool{
        unordered_set<int> seen;
        vi tmp;
        // case-1 between 0 and a1
        int l = 0, r = a[0]-m;
        while(sz(seen)<k && l<=r){
            if(!seen.count(l)){
                tmp.push_back(l);
                seen.insert(l);
            }
            l++;
        }
        if(sz(seen)>=k) {pos = tmp; return true;}
        
        // case 2 between a1 to an
        f(i,1,n){
            int first = a[i-1] + m;
            int last = a[i] - m;
            while(sz(seen)<k && first<=last){
                if(!seen.count(first)){
                    tmp.push_back(first);
                    seen.insert(first);
                }
                first++;
            }
            if(sz(seen)>=k) break;
        }
        if(sz(seen)>=k) {pos = tmp; return true;}

        // case 3 between an and x
        l = a[n-1]+m; r = x;
        while(sz(seen)<k && l<=r){
            if(!seen.count(l)){
                tmp.push_back(l);
                seen.insert(l);
            }
            l++;
        }
        pos = tmp;
        //cout << sz(seen) << endl;
        return sz(seen)>=k;
    };


    int s = 0, e = 1e9;
    int ans = 0;
    while(s<=e){
        int m = (e-s)/2 + s;
        //cout << m << ' ' << helper(m) << endl;
        if(helper(m)){
            ans = m;
            s = m+1;
        }
        else e = m-1;
    }
    //cout << ans << endl;
    helper(ans);
    //_print(pos);
    for(auto& x:pos) cout << x << ' ';
    cout << endl;

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