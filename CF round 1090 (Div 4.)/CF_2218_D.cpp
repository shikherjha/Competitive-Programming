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
const int n = 2e5;
vi primes;
vi sieve(int n) {
    vi isPrime(n+1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i*i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i*i; j <= n; j += i) isPrime[j] = 0;
        }
    }
    for (int i=2; i<=n; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
    return isPrime;
}
/*
    again a good trick problem
    gcd - > is just hcf for those who don't know
    we need to get gcd of adjacent elements different

    simple trick:
    if we want to fix gcd between two elements to one single value, how do we do that
    ..... yep we take 2 prime numbers beacause gcd (prime1, prime2 )  = 1
    e.g gcd (3,5) = 1
    but here we want then different so want we can do

    chain rule
    lets say (p1, p2, p3, p4, p5...) are primes
    we can do'
    a = p1 * p2
    b = p2* p3
    c = p3* p4 and so on
    look here gcd (a,b) -> they have p2 common and gcd(p1,p3) would be 1 as they are just primes they won't have
    any common factors, there gcd(a,b) = p2 and gcd(b,c) = p3 and so
    if p1, p2, p3 is just different prime numbers that just the answer, we take product of
    primes[i]*primes[i+1]

    Here, the learning thing is seive method to precompute primes array
    learn about this it's very important

    so if you wasn't able to do this no worries, this is where real learning curve starts, before this problem
    you didn't needd any data structure or complex algorithms
    generally from 4th things picks pace not very complicated but still, kudos if you tried this one
*/

void solve() {
    int N; cin >> N;
    for (int i=0; i<N; i++) {
        cout << primes[i] * primes[i+1] << ' ';
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
    sieve(n);
    while (t--) solve();

    return 0;
}