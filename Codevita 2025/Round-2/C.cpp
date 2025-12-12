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
 Intuition: So the problem seems quite straight forward, rotating a bar by 90 degrees only change the y coordinate never the x-coordinate
 - By this observation we can calculate, the different possible drop point of each given bar structure
 - for a single bar (lets say endpoints are (x1,y1) & (x2,y2)) then it can drop on 2 p only (x1,0) and (x2,0) that's it.
 - for a cross bar(lets say endpoints are 1(x1,y1),2(x2,y2), 3(x3,y3) and 4(x4,y4)) lets say 1 and 2 are upper end coordinates i.e
 the upper V in x, cause only that matters. so this bar can drop on 2 p only (x1,0), (x2,0)
 - so conclusion for each different bar structure(single or cross) only 2 distinct drop point is possible
 - Now we just have to check for each bar if it's reachable from the ball drop point, by any combination, if yes then those 2 coordinates
 will be included in the answer
 - So for n bars, the max distinct coordinates in the answer can be 2*n  
 - Also it is given that we can rotate 90 degree instantly as well, but the i believe according to problem statement the ball will
 always slide along the bar to the edge and then fall down and we can only tilt a bar once
 - simulation and checking which bars is reachable or not should be precise.
*/
struct bar {
    int id;
    int x1, y1, x2, y2;
};

int n;
vector<bar> bars;
vi cross; 
set<int> p;
map<pair<int,int>, bool> vis; 

// Helper to detect if two bars form an X
bool helper(bar& a, bar& b){
    int m1=(a.y2-a.y1)/(a.x2-a.x1);
    int m2=(b.y2-b.y1)/(b.x2-b.x1);

    if(m1==m2) return false; 

    double det=m1-m2;
    double ix = (b.y1-a.y1 + m1*a.x1 - m2*b.x1)/det;
    bool ans = (ix>min((double)a.x1, (double)a.x2) + 1e-9 && ix<max((double)a.x1, (double)a.x2)-1e-9 &&
                ix>min((double)b.x1, (double)b.x2) + 1e-9 && ix<max((double)b.x1, (double)b.x2)-1e-9);
    return ans;
}

void dfs(int curr_x, int curr_y, int flag1 = -1, int flag2 = -1) {
    if (vis.count({curr_x, curr_y})) return;
    vis[{curr_x, curr_y}]=true;

    int idx = -1;
    double maxi = -1e18; 

    f(i,0,n){
        if(i==flag1 || i==flag2) continue; 
        int lx = min(bars[i].x1, bars[i].x2);
        int rx = max(bars[i].x1, bars[i].x2);
        if(curr_x>=lx && curr_x<=rx) {
            int m = (bars[i].y2 -bars[i].y1)/(bars[i].x2- bars[i].x1);
            int by = m*(curr_x-bars[i].x1)+bars[i].y1;
            if(by < curr_y) { 
                if(by>maxi) {
                    maxi = by;
                    idx = i;
                }
            }
        }
    }
    if(idx==-1) {
        p.insert(curr_x);
        return;
    }
    int b_idx = idx;
    int p_idx = cross[b_idx];
    vpi tmp;

    if(p_idx!=-1) {
        vpi p;
        p.push_back({bars[b_idx].x1, bars[b_idx].y1});
        p.push_back({bars[b_idx].x2, bars[b_idx].y2});
        p.push_back({bars[p_idx].x1, bars[p_idx].y1});
        p.push_back({bars[p_idx].x2, bars[p_idx].y2});

        sort(p.begin(), p.end(), [](auto& a, auto& b){
            return a.second > b.second;
        });
        tmp.push_back(p[0]);
        tmp.push_back(p[1]);
        for (auto it:tmp) dfs(it.first,it.second,b_idx,p_idx);
    } else{
        tmp.push_back({bars[b_idx].x1, bars[b_idx].y1});
        tmp.push_back({bars[b_idx].x2, bars[b_idx].y2});
        for(auto it:tmp) dfs(it.first,it.second,b_idx,-1);
    }
}

void solve() {
    cin >> n;
    bars.clear();
    bars.resize(n);
    cross.assign(n, -1);
    p.clear();
    vis.clear();

    f(i,0,n){
        bars[i].id = i;
        cin >> bars[i].x1 >> bars[i].y1 >> bars[i].x2 >> bars[i].y2;
    }
    int x, y;
    cin >> x >> y;
    f(i,0,n){
        f(j,i+1,n){
            if(helper(bars[i], bars[j])) {
                cross[i] = j;
                cross[j] = i;
            }
        }
    }
    dfs(x,y);
    for(int p : p) {
        cout << p << " " << 0 << endl;
    }
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