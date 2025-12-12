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
const int MAX = 1e9;
const int MIN = 1e-9;

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
// intuitions:
    // The rectilinear figure and the the quadrilateral covering it whole will have the same loss
    // in area with decrease in side, so we can calculate for the (rectangle or square) we have to
    // maximize the volume i.e area*x  (x being the height), 
    // For a rectangle the area is length*breadth so new will be (length-2x)*(breadth-2x)
    // volume will be area*x
    // now we will look for x in range [0.1,(y-0.1)/2] which will maximize the volume
    // y here denotes the minimum edge/side length of the figure
    // from here we will find the optimal h
    // now have to calculate the area of the reduced figure and multiply by the h that's the answer
void solve() {
    int n; 
    cin >> n;
    vector<pair<double, double>> coord;
    f(i,0,n){
        int x, y; cin >> x >> y;
        coord.push_back({x,y});
    }

    double a = 0.0, P = 0.0;
    vector<double> edges;
    f(i,0,n){
        int j = (i+1) % n;
        double x1 = coord[i].first, y1 = coord[i].second;
        double x2 = coord[j].first, y2 = coord[j].second;
        a += x1 *y2 -x2 *y1;
        double dx = x2-x1, dy = y2-y1;
        double len = sqrt(dx*dx +dy*dy);
        P +=len;
        edges.push_back(len);
    }
    a = fabs(a)*0.5;

    // finding maximum H from the constrained intuition
    double maxH = MAX;
    for (double x : edges) {
        maxH = min(maxH, (x-0.1)/2.0);
    }
    if (maxH<0.1-MIN) {
        cout << fixed << setprecision(2) << 0.00 << endl;
        return;
    }

    double ans = 0.0;
    for (double i = 0.1;i<= maxH +MIN; i += 0.1) {
        double area_in = a-P*i + 4.0*i*i;
        if (area_in < 0) area_in = 0;
        double vol = area_in * i;
        if (vol > ans) ans = vol;
    }

    cout << fixed << setprecision(2) << ans << endl;
}

int32_t main() {
    fastio();

#ifdef LOCAL
    freopen("inputf.in", "r", stdin);
    freopen("output.in", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}