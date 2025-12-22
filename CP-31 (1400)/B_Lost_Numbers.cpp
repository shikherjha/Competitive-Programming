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
//#define endl '\n'

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
int query(int i, int j){
    cout << "?" << ' ' << i << ' ' << j << "\n";
    int x; cin >> x;
    cout << endl;
    return x;
}
vi helper(pair<int,int>p1, pair<int,int>p2 ){
    vi res;
    if(p1.first==p2.first){
        res.push_back(p1.first);
        res.push_back(p1.second);
        res.push_back(p2.second);

    }
    else if (p1.first==p2.second){
        res.push_back(p1.first);
        res.push_back(p1.second);
        res.push_back(p2.first);
    }
    else if (p1.second == p2.first){
        res.push_back(p1.second);
        res.push_back(p1.first);
        res.push_back(p2.second);
    }
    else {
        res.push_back(p1.second);
        res.push_back(p1.first);
        res.push_back(p2.first);
    }
    return res;
}

void solve() {
    unordered_map<int,pair<int,int>> mp;
    vector<int> a = {4, 8, 15, 16, 23, 42};
    f(i,0,6){
        f(j,i+1,6){
            mp[a[i]*a[j]] = make_pair(a[i],a[j]);
        }
    }
    // first 2 queries for 1 to 3 elements
    int p1 = query(1,2);
    int p2 = query(1,3);
    auto it1 = mp[p1], it2 = mp[p2];
    // cout << it1.first << ' ' << it1.second << "\n";
    // cout << it2.first << ' ' << it2.second << "\n";
    vi ans1 = helper(it1,it2);

    // second 2 queries for 4 to 6 elements
    int p3 = query(4,5);
    int p4 = query(4,6);
    auto it3 = mp[p3], it4 = mp[p4];
    vi ans2 = helper(it3,it4);
    cout << "! ";
    for(int x: ans1) cout << x << ' ';
    for(int x:ans2) cout << x << ' ';
    cout << endl;

}

int32_t main() {
    //fastio();

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}