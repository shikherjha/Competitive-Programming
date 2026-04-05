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
    Multiple answers this means, we can see something,
    first though is something around 2 to the power

    initial though doesn't work, a bit wise apporach might be better since we have to reduce sum of gap between 
    x and p & y and q. we will try to assign same bits to them only we can't do this at places where both x and y
    have 1, then there will be 2 cases on top of mind
        - Give that bit to p, this will ensure x=p in that case, here we still neeed to minimize q, we will give 0 at 
        that place (say k), vice versa is also possible
        - maybe give all other positions lesser than that 0
         
        Naah giving 0 won't work, (case 4,4) failed
        maybe a high and a low submask will help, we can assign similar bits at places >k, and for places <k will be set bit
        only if x has 0 at that place
        this is for both the cases



        New cases, that I missed, overflow conditions we can take p or q greater than x or y, something like a bit set at a
        position >k    
*/

void solve() {
    int x,y; cin >> x >> y;
    if(x==0 && y==0){
        cout << 0 << ' ' << 0 << endl;
        return;
    }
    int min_cost = -1, P = -1, Q = -1;
    auto helper = [&](int p, int q)->void{
        int cost = abs(p-x) + abs(q-y);
        if(min_cost==-1 || cost<min_cost){
            min_cost = cost;
            P = p; Q = q;
        }
    };
    int k = -1; // msb where contradiction happens
    rf(i,30,0){
        if(((x>>i)&1) && ((y>>i)&1)){
            k = i;
            break;
        }
    }
    if(k==-1){
        cout << x << ' ' << y << endl;
        return;
    }
    int high = (~0)<<(k+1), low = (1LL<<k)-1;
    // case - 1 p takes the bit
    int p1 = x, q1 = (y&high) | (low&(~x));
    helper(p1,q1);
    // case -2 q takes the bit
    int q2 = y, p2 = (x&high) | (low&(~y));
    helper(p2,q2);
    // case - 3 p overflows
    int t = (1<<(k+1));
    int mask = ~(t-1);
    int p3 = (x&mask)+t, q3 = y&(~p3);
    helper(p3,q3);
    // case - 4 q overflows
    int q4 = (y&mask)+t, p4 = x&(~q4);
    helper(p4,q4);

    cout << P << ' ' << Q << endl;
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