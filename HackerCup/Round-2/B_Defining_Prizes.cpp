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
template<class T, class V> void _print(pair<T,V> it) { cerr << "{"; _print(it.first); cerr << ","; _print(it.second); cerr << "}"; }
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
int val = 1;
int n,m;

void solve() {
    cin >> n >> m;
    vi a(n), b(m);
    f(i,0,n) cin >> a[i];
    f(i,0,m) cin >> b[i];


    unordered_map<int,int> freq;
    freq.reserve(min((int)1e5, n));
    for(int x : a) freq[x]++;

    vpi tmp;
    tmp.reserve(freq.size());
    for(auto &it:freq) tmp.emplace_back(it.first, it.second);
    sort(all(tmp), greater<pair<int,int>>()); 

    vi cnts;
    cnts.reserve(tmp.size());
    for(auto &it:tmp) cnts.push_back(it.second);

    int k = cnts.size();

    vi prefCnt(k,0), prefSum(k,0);
    f(i,0,k){
        prefCnt[i] = cnts[i] +(i?prefCnt[i-1]:0);
        prefSum[i] = (int)cnts[i]*i +(i?prefSum[i-1]:0);
    }

    sort(all(b));
    vi pref_b(m,0);
    f(i,0,m) pref_b[i] = b[i] + (i?pref_b[i-1]:0);

    auto helper = [&](int cnt)-> int {
        if (m==0) return (int)0;
        int idx = upper_bound(b.begin(), b.end(), cnt) - b.begin(); 
        int sum1 = (idx==0?0:pref_b[idx-1]);
        int cnt1 = m - idx;
        return sum1 + cnt1 * cnt;
    };

    int ans = 0;
 
    f(t,1,k+1) {
        if(t> m) break; 
        int cnt = prefCnt[t-1]; 
        int sum_j = prefSum[t-1];
        int mini = (int)t * cnt - sum_j;
        int sum2 = helper(cnt);
        if (mini <= sum2) ans = max(ans, cnt);
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