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
 Intuiton: we want to reach to a '0' in the inner circle (say at index x), we can reach a zero either a jumping down from an zero (if present at index
 2*x-1, 2*x) or we have travlled from a string of consective zero to that one.
 Basically, it boils down to different jump scenarios, we can only jump from outer level '0' (say index i) to an inner level zero to
 index 2*i-1 or 2*i. that's the only 2 options if there's zero present in the inner level at that index
 It feels like a dp problem we need to find the minimum across all possible jumps and traversal
 - Given the constraints outer most can have 4*1032 elements at max edge case.
 - It can be solved using classical dp with some clever transition equations
 - we can create a dp table, assign inf to every position where there is one. And for zeroes we can compute, there are 2 possible options 
 we have at a given zero (either we can jump down to idx/2, idx+1/2 if there's a zero there or we can keep moving in the current level
 idx+1 or idx-1 given our direction we choose) if both of these options is not valid we can not reach from that index so we can assign inf to
 that index.
 - It involves visiting all the substates as well as not visiting any twice, gives a feel of BFS as well, we can maintain a queue and
 do a constrained BFS as well to find the minimum (shorted distance from start -> goal).
*/

void solve() {
    int n;
    cin >> n;
    vector<string> ring(n);
    f(i,0,n) cin >> ring[i];

    vvi dist(n);
    f(i,0,n) dist[i].assign(sz(ring[i]),-1);

    deque<pair<int,int>> q;
    int outer = n - 1;
    int osz = sz(ring[outer]);
    f(j,0,osz) {
        if(ring[outer][j]=='0') {
            dist[outer][j]=1;
            q.push_back(make_pair(outer,j));
        }
    }

    int ans =1e9;
    while(!q.empty()) {
        pair<int,int> p = q.front(); q.pop_front();
        int lvl = p.first;
        int idx = p.second;
        int d = dist[lvl][idx];

        if(lvl==0) {
            ans=d;
            break;
        }

        int sze = sz(ring[lvl]);
        int a = (idx+1)%sze;
        int b = (idx-1+sze)%sze;

        if(ring[lvl][a]=='0' && dist[lvl][a]==-1){
            dist[lvl][a] = d + 1;
            q.push_back(make_pair(lvl,a));
        }
        if(ring[lvl][b]=='0' && dist[lvl][b] == -1) {
            dist[lvl][b] = d + 1;
            q.push_back(make_pair(lvl,b));
        }

        if(lvl-1>=0) {
            int i = idx / 2;
            if (ring[lvl-1][i] == '0' && dist[lvl-1][i]==-1) {
                dist[lvl-1][i]= d + 1;
                q.push_back(make_pair(lvl - 1,i));
            }
        }

        if(lvl+1<n) {
            int o1= 2*idx;
            int o2 = 2*idx+1;
            int outSz = sz(ring[lvl+1]);
            if(o1<outSz && ring[lvl + 1][o1] == '0' && dist[lvl + 1][o1] == -1) {
                dist[lvl + 1][o1] = d+1;
                q.push_back(make_pair(lvl + 1, o1));
            }
            if(o2 < outSz && ring[lvl + 1][o2] == '0' && dist[lvl + 1][o2] == -1) {
                dist[lvl + 1][o2] = d + 1;
                q.push_back(make_pair(lvl + 1, o2));
            }
        }
    }

    if (ans==1e9) ans=-1;
    cout << ans;
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