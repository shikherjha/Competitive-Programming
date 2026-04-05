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
    from here good puzzles start
    we have n, we need to create a permutation of 3*n. a permutation is basically sequence containing 1 to 3*n value
    without repetition or misssing (it's important you'll see this very often)

    trick: median is the middle element after sorting
    say (A,B,C) is your triplet 
    we want to maximize sum of medians, 
    from what i see, we need to have as max possible values as possible
    A is just garbage, we just fill smallest value in A
    we have n triplets -> n A's -> we use 1 to n as A
    this leaves values n+1 to 3*n for B and C
    now in those B would always be second maximum, so why not I take adjacent  elements as B and C

    let's take example
    n = 2, therefore 6 elements (1,2,3,4,5,6)
    we will have 2 triplets (a,b,c) (d,e,f)
    for A (a,d) -> we take first n smallest values (1,2)
    now we are left with (3,4,5,6)
    for B and C we take adjacent (3,4) and (5,6)
    this makes our sum (3+5) = 8, try other ways you can't find any other

    (1,3,4) (2,5,6)
    so what is formula for this
    (i,n+2*i-1, n+2*i)
    so we will just print this


    again no data structure, just observation
    tip: in codeforces you will see many problems where output can be anything, the order or values doesn't matter
    these questions you need to come up withb your own trick, in problem look for multiple answer possible, output any
    kind of lines
*/
void solve() {
    int n; cin >> n;
    for (int i=1; i<=n; i++) {
        cout << i << ' ' << n+2*i-1 << ' ' << n+2*i << ' ';
    }
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