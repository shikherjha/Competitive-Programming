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

const int MOD = 676767677;
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
bool helper(vi& a){
    int n = sz(a);
    f(i,0,n-1){
        if(a[i]!=a[i+1]){
            return false;
        }
    }
    return true;
}

void solve() {
    int n; cin >> n;
    vi a(n);
    f(i, 0, n) cin >> a[i];
    
    if(helper(a)){
        if(n%2==0){
            if(a[0] == (n/2) + 1 || a[0] == n/2){
                cout << 1 << endl;
            }
            else{
                cout << 0 << endl;
            }
        }
        else{
            if(a[0] == (n/2)+1){
                cout << 2 << endl;
            }
            else{
                cout << 0 << endl;
            }
        }
        return;
    }
    int prev = 0;
    f(i,0,n-1){
        if(abs(a[i+1]-a[i])>1){
           cout << 0 << endl;
           return;
        }
        if(prev*(a[i+1]-a[i])<0){
            cout << 0 << endl;
            return;
        }
        prev = a[i+1]-a[i];
    }
   
    vector<char> v(n,'-');
    f(i,0,n-1){
        if(a[i]==a[i+1]) continue;
        if(a[i+1]-a[i]==1){
            v[i] = 'L';
            v[i+1] = 'L';
        }
        else{
            v[i] = 'R';
            v[i+1] = 'R';
        }
    }
    //_print(v);
    queue<int> q;
    f(i,0,n){
        if(v[i]!='-') q.push(i);
    }
    while(!q.empty()){
        int x = q.front(); q.pop();
        if(x<n-1){
            if(v[x+1]=='-'){
                v[x+1] = 'R' + 'L' - v[x];
                q.push(x+1);
            }
            else{
                if(v[x+1]!='R'+'L'-v[x] && a[x]==a[x+1]){
                    cout << 0 << endl;
                    return;
                }
            }
        }
        if(x>0){
            if(v[x-1]=='-'){
                v[x-1] = 'R'+'L'-v[x];
                q.push(x-1);
            }
            else{
                if(v[x-1]!='R'+'L'-v[x] && a[x]==a[x-1]){
                    cout << 0 << endl;
                    return;
                }
            }
        }
    }
    //_print(v);
    vi pre(n), suff(n);
    pre[0] = 0; suff[n-1] = 0;
    f(i,1,n){
        pre[i] = pre[i-1] + ((v[i-1]=='L')? 1:0) ;
    }
    rf(i,n-2,0){
        suff[i] = suff[i+1] + ((v[i+1]=='R')? 1:0);
    }
    //_print(pre);
    //_print(suff);
    f(i,0,n){
        if(a[i]!=pre[i]+suff[i]+1){
            cout << 0 << endl;
            return;
        }
    }
    cout << 1 << endl;
    

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