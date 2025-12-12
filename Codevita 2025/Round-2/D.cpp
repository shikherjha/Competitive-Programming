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
    Intuition: So it's basically a 3-d grid traversing problem with a different movement constraints
    - (z,x,y) -> represents z floor and normal (x,y) coordinates
    - convention here there are different layers (in between layers movements in front and back movement), and (row-col is a vertical
    structure) rows(x) being different vertical floors, and col(y) being moving in same floor left and right movement.
    - There different kinds of cell, that denotes different movements
    - E: empty cell or blocked cell as there is no floor to walk
    - D: normal cell it involves moving withing a level i.e (left,right,front,back and conditional diagonal movements), in 
        conclusion moving within rows and layers and not
        columns. {(0,1,0), (0,-1,0), (1,0,0), (-1,0,0)} these are the 4 possible moves
        So from a D cell we move diagonally down (either left or right) only if that down element is L for left and R for right movement,
        that is D cell is end of a staircase cell (R,L,F,B)

    - R: this is connector (like staircase), it connects a lower floor (column to a higher column i.e lower column to higher right)
        it connects (z,x,y) <-> (z,x+1,y-1), it's a 2 way connector and we can move in between columns.
    -L: this is connector (like staircase), it connects a lower floor (column to a higher column i.e lower column to higher left)
        it connects (z,x,y) <-> (z,x+1,y+1), it's a 2 way connector and we can move in between columns.
    - F: It's connector between layers and floors (z,x,y) <-> (z+1,x-1,y) again a two way connector
    -B: It's connector between layers and floors (z,x,y) <-> (z+1,x+1,y) again a two way connector

    -these are the conventions and movement constraints. Now we have to find the minimum steps or shortest path from start to goal
       
    - This problem can be visualized as combination of gates and staircase in a 3-D cube. so D mean a room with 4 gates [to move left
    right, front and back only not vertical unless there's stairway connecting it] these doors are 2 way connection 2 way movements in and out,
     L and R are staircase connecting different vertical
        floors (difference 1) they are inclined floors, one right and one left. These stairs can be used for 2 way, that is we can move up to bottom
        as well as top to up
        F & B are also staircase but 2-d instead of 1-d, they connect in between layers and floors altogether. Again a 2 way movement.
    - This problem can be visualized as minimum steps need from start to goal allowing movement between gates and staircase only.
*/

struct p {
    int z, x, y;
};

void solve() {
    int s; cin >> s;
    vector<vector<string>> grid(s, vector<string>(s));
    f(z,0,s){
        f(x,0,s){
            cin >> grid[z][x];
        }
    }

    p start, goal;
    cin >> start.z >> start.x >> start.y;
    cin >> goal.z >> goal.x >> goal.y;

    if (grid[start.z][start.x][start.y] == 'E') {
        return; 
    }

    queue<p> q;
    q.push(start);
    vector<vvi> dist(s, vvi(s, vi(s, -1)));
    dist[start.z][start.x][start.y] = 0;

    auto helper = [&](int z, int x, int y) {
        return z >= 0 && z < s && x >= 0 && x < s && y >= 0 && y < s && grid[z][x][y] != 'E';
    };

    auto add = [&](int z, int x, int y, int d) {
        if (helper(z, x, y) && dist[z][x][y] == -1) {
            dist[z][x][y] = d + 1;
            q.push({z, x, y});
        }
    };

    while(!q.empty()) {
        p u = q.front();
        q.pop();

        if(u.z == goal.z && u.x == goal.x && u.y == goal.y) {
            cout << dist[u.z][u.x][u.y] << endl;
            return;
        }

        int d = dist[u.z][u.x][u.y];
        char t = grid[u.z][u.x][u.y];

        int dz[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        f(i,0,4){
            add(u.z + dz[i], u.x, u.y + dy[i], d);
        }

        if(t == 'L') add(u.z, u.x - 1, u.y - 1, d);
        if(t == 'R') add(u.z, u.x - 1, u.y + 1, d);
        if(t == 'F'){
            add(u.z + 1, u.x + 1, u.y, d);
            add(u.z - 1, u.x - 1, u.y, d);
        }
        if(t=='B') {
            add(u.z + 1, u.x - 1, u.y, d);
            add(u.z - 1, u.x + 1, u.y, d);
        }
        if(helper(u.z, u.x + 1, u.y + 1) && grid[u.z][u.x + 1][u.y + 1] == 'L')
            add(u.z, u.x + 1, u.y + 1, d);
        
        if(helper(u.z, u.x + 1, u.y - 1) && grid[u.z][u.x + 1][u.y - 1] == 'R')
            add(u.z, u.x + 1, u.y - 1, d);

        if(helper(u.z - 1, u.x - 1, u.y) && grid[u.z - 1][u.x - 1][u.y] == 'F')
            add(u.z - 1, u.x - 1, u.y, d);
        if(helper(u.z + 1, u.x + 1, u.y) && grid[u.z + 1][u.x + 1][u.y] == 'F')
            add(u.z + 1, u.x + 1, u.y, d);

        if(helper(u.z - 1, u.x + 1, u.y) && grid[u.z - 1][u.x + 1][u.y] == 'B')
            add(u.z - 1, u.x + 1, u.y, d);
        if(helper(u.z + 1, u.x - 1, u.y) && grid[u.z + 1][u.x - 1][u.y] == 'B')
            add(u.z + 1, u.x - 1, u.y, d);
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