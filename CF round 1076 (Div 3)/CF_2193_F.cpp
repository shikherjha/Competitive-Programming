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
    1. clearly it can be seen that the movement is x is non-decreasing that means we can't move back
    2. Sorting the coordinates vector based on x, in increasing order is the way to go
    3. Now comes the tricky part, the movement in y can be done in both way
    4. On top of my mind, the first thought is to move in one direction first then to other directions
        - In other words, lets say we are at pivot, there are coordinates on the upper half and there are
          corrdinates on the lower half, the optimal greedy way is to move in one direction first rather than
          zig-zag pattern.
    5. Next point is choosing the initial movement direction that needs to be optimal, there are 2 deciding factors
        if we go in 1 direction we have to comeback to move in other this will cost in 2*intial direction distance
    Scratch this found the logic, we will move in opposite direction first, i.e  fuck it
    Update: greedy failed had the right intuition switching to motherfucking dp
*/
void solve() {
    int n,x1,y1,x2,y2; cin >> n >> x1 >> y1 >> x2 >> y2;
    vi X(n), Y(n);
    f(i,0,n) cin >> X[i];
    f(i,0,n) cin >> Y[i];
    map<int,int> maxi,mini;
    f(i,0,n){
        if(mini.count(X[i])){
            mini[X[i]] = min(mini[X[i]],Y[i]);
            maxi[X[i]] = max(maxi[X[i]],Y[i]);
        }
        else{
            mini[X[i]] = Y[i];
            maxi[X[i]] = Y[i];
        }
    }
    // dp0 -> towards mini
    // dp1 -> towards maxi
    int dp0 = 0, dp1 = 0;
    int prev_y0 = y1, prev_y1 = y1;
    for(auto& it:mini){
        int x = it.first;
        int minY = it.second, maxY = maxi[x];
        int dis = maxY - minY;

        int next0 = min(dp0+abs(prev_y0-maxY),dp1+abs(prev_y1-maxY)) + dis;
        int next1 = min(dp1+abs(prev_y1-minY),dp0+abs(prev_y0-minY)) + dis;

        dp0 = next0; dp1 = next1;
        prev_y0 = minY; prev_y1 = maxY;
    }
    int ans = min(dp0 + abs(prev_y0 - y2), dp1 + abs(prev_y1 - y2));
    ans += x2-x1;
    cout << ans << endl;
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