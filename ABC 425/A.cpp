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
    string s;
    cin >> s;
    int n = s.size();

    // Simulation 1: treat every '2' as '0'
    stack<char> st1;
    f(i,0,n){
        char c = (s[i]=='2' ? '0' : s[i]);
        if(!st1.empty() && st1.top() == c)
            st1.pop();
        else
            st1.push(c);
    }
    
    // Simulation 2: treat every '2' as '1'
    stack<char> st2;
    f(i,0,n){
        char c = (s[i]=='2' ? '1' : s[i]);
        if(!st2.empty() && st2.top() == c)
            st2.pop();
        else
            st2.push(c);
    }
    
    // Simulation 3: dynamically decide the allocation of '2'
    // When a '2' is encountered:
    //    if the stack is non-empty and the top is a determined digit ('0' or '1'),
    //         choose that digit to cancel.
    //    otherwise, push a '2' as a wildcard.
    // When a determined digit ('0' or '1') is encountered and the top is a wildcard '2',
    //         we decide to convert the wildcard to that digit to cancel.
    stack<char> st3;
    f(i,0,n){
        char c = s[i];
        if(c=='2'){
            if(!st3.empty() && (st3.top()=='0' || st3.top()=='1')){
                st3.pop();
            } else {
                st3.push('2');
            }
        } else { // c is '0' or '1'
            if(!st3.empty()){
                if(st3.top() == c){
                    st3.pop();
                } else if(st3.top()=='2'){
                    // Convert the wildcard on top to c to cancel it
                    st3.pop();
                } else {
                    st3.push(c);
                }
            } else {
                st3.push(c);
            }
        }
    }
    
    int ans = min({(int)st1.size(), (int)st2.size(), (int)st3.size()});
    cout << ans << endl;
}

int32_t main(){
    fastio();

#ifdef LOCAL
    freopen("inputf.in","r",stdin);
    freopen("output.in","w",stdout);
    freopen("error.txt","w",stderr);
#endif

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}