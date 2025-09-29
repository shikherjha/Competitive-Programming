#include <bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define vvi vector<vi>
#define pii pair<int,int>
#define vpi vector<pii>
#define f(i,u,v) for(int i=u; i<v; i++)
#define rf(i,u,v) for(int i=u; i>=v; i--)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define endl '\n'

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)

#ifdef LOCAL
#define dvg(x) cerr << #x << " = "; _print(x); cerr << endl;
#else
#define dvg(x)
#endif

template<class T> void _print(T x) { cerr << x; }
template<class T, class V> void _print(pair<T,V> p) { cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}"; }
template<class T> void _print(vector<T> v) { cerr << "["; for (auto i : v) { _print(i); cerr << " "; } cerr << "]"; }

const int MOD = 1000000007;
const int INF = 1000000000000000000LL;

int mod_add(int u, int v) { return (u % MOD + v % MOD) % MOD; }
int mod_suv(int u, int v) { return (u % MOD - v % MOD + MOD) % MOD; }
int mod_mul(int u, int v) { return (u % MOD * v % MOD) % MOD; }
int mod_pow(int u, int v) {
    int res = 1;
    u %= MOD;
    while (v) {
        if (v & 1) res = mod_mul(res, u);
        u = mod_mul(u, u);
        v >>= 1;
    }
    return res;
}
int mod_inv(int u) { return mod_pow(u, MOD - 2); }

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
void vfs(int start, vi adj[], vi &vis) {
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

int helper(int u, int v, int k){
    return u * (k+1) + v;
}
// Initial thought of choosing the node with higher degree is failing when there's a tie in the degree, will have to choose the one which
// will give maximum answer. So now there is can be base gain with the current friend and some additional gain possible with new friends
// The new gain can be of 3 kinds like, if in a pair 1 is missing, (in this a subcase is also possible of self gain, like the pair comes out as self node)
// then there can be gain as a pair as we are adding 2 friends if those 2 forms a comment pair then that will also be the part of additonal gain  as well

void solve(){
    int n, m, k; cin >> n >> m >> k;
   
    vector<bool> flag(k+1, false);
    vi a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
        flag[a[i]] = true;
    }
   
    int cnt = 0;
    // gain1 -> gain when only 1 is missing in the pair
    // gain2 -> self gain when the 1 is missing 
    // gain3 -> gain for the pair when 2 are missing
    unordered_map<int,int> gain1;  
    unordered_map<int,int> gain2; 
    unordered_map<int,int> gain3; 
     
    vpi pairs;
    f(i,0,m){
        int u, v; 
        cin >> u >> v;
        pairs.push_back({u,v});
        if(u == v){
            if(flag[u])
                cnt++;
            else
                gain2[u]++;
        } else {
            bool t1 = flag[u];
            bool t2 = flag[v];
            if(t1 && t2)
                cnt++;
            else if(t1 && !t2)
                gain1[v]++;
            else if(!t1 && t2)
                gain1[u]++;
            else {
                
                int u2 = min(u, v), v2 = max(u, v);
                int key = helper(u2, v2, k);
                gain3[key]++;
            }
        }
    }
    
    unordered_map<int,int> tmp1;
    set<int> seen;
    for(auto &p : gain2){
        int u = p.first;
        if(!flag[u]){
            tmp1[u] += p.second;
            seen.insert(u);
        }
    }
    for(auto &p: gain1){
        int u = p.first;
        if(!flag[u]){
            tmp1[u] += p.second;
            seen.insert(u);
        }
    }
    
    for(auto &p: gain3){
        int key = p.first;
        int u = key / (k+1), v = key % (k+1);
        if(!flag[u] && !seen.count(u)){
            seen.insert(u); 
            tmp1[u] += 0;
        }
        if(!flag[v] && !seen.count(v)){
            seen.insert(v);
            tmp1[v] += 0;
        }
    }
   
    int g1 = 0;
    for(auto u : seen)
        g1 = max(g1, tmp1[u]);
    
    int g2 = 0;
    vector<int> tmp2;
    for(auto u : seen)
        tmp2.push_back(tmp1[u]);
    sort(tmp2.begin(), tmp2.end(), greater<int>());
    if(sz(tmp2) >= 2)
        g2 = tmp2[0] + tmp2[1];
    else if(sz(tmp2) == 1)
        g2 = tmp2[0];
    
    int g3 = g2;
    
    for(auto &p : gain3){
        int key = p.first;
        int val = p.second;
        int u = key/(k+1), v = key%(k+1);
        if(seen.count(u) && seen.count(v)){
            int temp = tmp1[u] + tmp1[v] + val + (val == 0 ? 1 : 0);
            g3 = max(g3, temp);
        }
    }
     
    cout << max(cnt, cnt + max(g1, g3)) << endl;
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