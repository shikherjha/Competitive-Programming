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

void solve(){
    int n, m, c;
    cin >> n >> m >> c; // number of gas stations, budget, maximum tank capacity
    vi price(n), dis(n);
    f(i,0,n){
        int x, y;
        cin >> x >> y;
        dis[i] = x;
        price[i] = y;
    }

    // Given, we start with an empty tank at station 1, which is at distance 0, and we need to maximize the distance we can travel with budget m/
    // Greedy approach: travel from 1 to n gas stations, if it the gas station has the minimum price in the remaining gas stations, 
    //we will try to fill the tank as much as possible.
    // We will use a min-heap to keep track of the minimum price gas station in the remaining gas stations.
    // now for non-minimun price gas stations, we will only buy enough fuel to reach the next gas station. but there is a catch
    // if it is the maximum price and we can reach the next gas station, we will not buy any fuel from this gas station.
    // if we cannot reach the next gas station, we will buy enough fuel to reach the next gas station.
    // if we cannot reach the next gas station even after buying the maximum fuel, we will return the distance we traveled so far.
    // at the last gas station we will buy maximum fuel possible.
    // if the maximum price gas station is the fist gas station, we will buy enough fuel to reach the next gas station.
    //if the maximum price gas station is the last gas station, we will buy maximum fuel possible.


    // there can be alternate dp approach to solve this problem as well
    // but given the constraints, we can do only O(n) or O(n log n) approach.
    
    // Precompute min and max price from station i to the last station.
    vi dp1(n), dp2(n);
    dp1[n-1] = price[n-1];
    dp2[n-1] = price[n-1];
    for(int i = n-2; i >= 0; i--){
        dp1[i] = min(price[i], dp1[i+1]);
        dp2[i] = max(price[i], dp2[i+1]);
    }
    
    int curr_fuel = 0;  // fuel in the tank at current station
    
    if(price[0] == dp1[0]){
        // This is the cheapest among all. Fill as much as possible.
        int buy = min(c - curr_fuel, m / price[0]);
        curr_fuel += buy;
        m -= buy * price[0];
    }
    else{
        // Not cheapest; buy just enough fuel to reach next station.
        int need = dis[1] - dis[0];
        int buy = need - curr_fuel; // curr_fuel is 0 initially so buy exactly 'need'
        // Make sure we do not buy beyond capacity and that we have the budget.
        buy = min(buy, c - curr_fuel);
        if(buy * price[0] > m) buy = m / price[0];
        curr_fuel += buy;
        m -= buy * price[0];
    }
    // Travel from station 0 to station 1.
    {
        int travel = dis[1] - dis[0];
        curr_fuel -= travel;  // reduce fuel by distance traveled
        // If we run out in transit, we cannot reach station1.
        if(curr_fuel < 0){
            cout << dis[0] + (curr_fuel + travel) << endl;
            return;
        }
    }
     
    // Process intermediate stations: i from 1 to n-2.
    f(i,1,n-1){
        // At arrival, subtract fuel used from previous leg.
        if(i > 0){
            // (Already deducted on travel, so nothing extra to deduct here.)
        }
        // fuel needed to reach next station:
        int need = dis[i+1] - dis[i];
 
        // Decision depending on station's price relative to remaining stations
        if(price[i] == dp1[i]){
            // This station is the cheapest among the remaining.
            // Fill as much as possible.
            int buy = min(c - curr_fuel, m / price[i]);
            curr_fuel += buy;
            m -= buy * price[i];
        }
        
        else{
            // A station with an intermediate price.
            // Only buy fuel if you cannot reach the next station.
            if(curr_fuel < need){
                int buy = need - curr_fuel;
                buy = min(buy, c - curr_fuel);
                if(buy * price[i] > m) buy = m / price[i];
                curr_fuel += buy;
                m -= buy * price[i];
            }
        }
 
        // Travel to the next station.
        curr_fuel -= need;
        if(curr_fuel < 0){
            // Could not reach next station, so maximum distance is current station's position + fuel available.
            cout << dis[i] << endl;
            return;
        }
    }
    
    int i = n-1;
    int buy = min(c - curr_fuel, m / price[i]);
    curr_fuel += buy;
    m -= buy * price[i];
    
    
    cout << dis[n-1] + curr_fuel << endl;
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
