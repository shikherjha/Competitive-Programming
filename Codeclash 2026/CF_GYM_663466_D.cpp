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
//#define endl '\n'

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
int query(int l, int r){
    cout << '?' << ' ' << l << ' ' << r << endl;
    int x; cin >> x;
    //cout << endl;
    return x;
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
    int n, k; cin >> n >> k;
    vector<vi> pos(k + 2);
    f(i,1,n+1) {
        if(query(i, i) == 1) pos[0].push_back(i);
    }
    auto helper = [&](int x)-> int{
        if(x == 0) return (n*(n + 1))/2;
        f(i,0,x) if(pos[i].empty()) return 0;
        int res = 0;
        vi ptr(x, 0);
        f(i,1,n+1) {
            int mini = i;
            bool flag = true;
            f(j,0,x) {
                while(ptr[j] < sz(pos[j]) && pos[j][ptr[j]] <= i) ptr[j]++;
                if(ptr[j] == 0) { flag = false; break; }
                mini = min(mini, pos[j][ptr[j] - 1]);
            }
            if(flag) res += mini;
        }
        return res;
    };

    if(pos[0].empty()) {
        if(k == 0) cout << "! " << (n *(n+1))/2 << endl;
        else cout << "! " << 0 << endl;
        return;
    }

    f(i,1,k+1) {
        vi& pos2 = pos[i-1];
        if(pos2.empty()) break;
        vi tmp; tmp.push_back(0);
        for(int x : pos2) tmp.push_back(x);
        tmp.push_back(n+1);

        f(j,0,sz(tmp)-1) {
            //if(tmp[j+1] - tmp[j] <= 1) continue;
            int l = tmp[j]+1;
            int r = tmp[j+1]-1;
            if(l>r) continue;
            if (query(l, r) > i) {
                int curL = l;
                while (curL <= r && query(curL, r) > i) {
                    int s = curL, e = r, first = -1;
                    while (s <= e) {
                        int mid = s + (e - s) / 2;
                        if (query(curL, mid) > i) { first = mid; e = mid - 1; }
                        else s = mid + 1;
                    }
                    if (first == -1) break;
                    pos[i].push_back(first);
                    curL = first + 1;
                }
            }
        }
        sort(all(pos[i]));
        pos[i].erase(unique(all(pos[i])), pos[i].end());
    }

    int ans1 = helper(k);
    int ans2 = helper(k + 1);
    cout << "! " << ans1 - ans2 << endl;
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