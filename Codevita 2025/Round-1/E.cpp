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
const double MIN = 1e-9;
const double PI = acos(-1.0);

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
void bfs(int s, vi adj[], vi &vis) {
    queue<int> q;
    q.push(s);
    vis[s] = 1;
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
// Intuitions:
    // Straight of the bat, first thing we need to check for intersection points
    // since constraints are low it can be done O(n^2) 
    // now for a closed figure to appear, they should be atleast 3 intersection points present


    // intuition for closed loop formation....
        // There must be a cycle like pattern within the lines containing the intersection points
        // example: lets say for 3 intersection point, 
            //  1st - l1 and l2
            // 2ns - l2 and l3
            // then 3rd must lie between l3 and l1
        // for checking this we have to store the lines containing the intersection point,
        // then maybe a set to check if there forms any cycle, it is mentioned in the problem'
        // that there can't be more than 1 closed figure
    //....
    // Now that we have found out the coordinates of closed figure (if exists) we can also store the
    // remaining total length that the computer can use
    // Now we will have to calculate the area of the enclosed figure, we can use the shoelace formula
    // for calculating that
    // now we have the area for human, coming back to the  computer we have the total remaining
    // stick sum available. 
        // ...
        // There is a intuition that the maximum sum is enclosed by a circle, but we can't create
        // a circle. lim n->inf An = max. so we will try to maximize the sides of the polygon and 
        // and by even distribution will come up with the max area
        // if that area is greater then the ouput is simple

using P=pair<double,double>; // first=x, second=y
double round_off(double v){ return floor(v*100.0 + 0.5) / 100.0; }
bool helper(const P &p, const P &p2, const P &q, const P &q2, P &ip) {
    double x1=p.first, y1 = p.second;
    double x2=p2.first, y2 = p2.second;
    double x3=q.first, y3 = q.second;
    double x4=q2.first, y4 = q2.second;

    double tmp=(x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);
    if(fabs(tmp)<MIN) {
        // parallel or collinear -> no single intersection point
        return false;
    }
    double a=x1*y2 - y1*x2;
    double b=x3*y4-y3*x4;
    double X=(a*(x3-x4)-(x1-x2)*b)/tmp;
    double Y=(a*(y3-y4)-(y1-y2)*b)/tmp;
    auto helper1=[](double a,double b,double v){
        if(a>b) swap(a,b);
        return v+1e-8>=a && v<=b +1e-8;
    };
    if(helper1(x1,x2,X) && helper1(y1,y2,Y) && helper1(x3,x4,X) && helper1(y3,y4,Y)) {
        ip.first =round_off(X);
        ip.second=round_off(Y);
        return true;
    }
    return false;
}
double dist(const P &a, const P &b){ 
    double dx =a.first-b.first, dy=a.second-b.second; 
    return sqrt(dx*dx+dy*dy); 
}
void solve() {
    int n; cin >> n;
    vector<pair<P,P>> lines;
    f(i,0,n){
        int x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        lines.push_back({P((double)x1,(double)y1), P((double)x2,(double)y2)});
    }
    map<pair<int,int>, int> mp; 
    vector<P> points;
    auto helper2 = [&](const P &p)->int{
        long long xi=llround(p.first * 100.0);
        long long yi=llround(p.second * 100.0);
        pair<int,int> key ={ (int)xi, (int)yi };
        auto it=mp.find(key);
        if (it!=mp.end()) return it->second;
        int i=sz(points);
        mp[key]=i;
        points.push_back(P(round_off(p.first), round_off(p.second)));
        return i;
    };
    f(i,0,n){
        f(j,0,n){
            P ip;
            if(helper(lines[i].first, lines[i].second, lines[j].first, lines[j].second, ip)) {
                helper2(ip);
            }
        }
    }
    if(points.empty()) {
        cout<<"Abandoned" << endl;
        return;
    }
    int m = sz(points);
    vector<vector<pair<double,int>>> pts(n);
    f(i,0,n){
        P a=lines[i].first, b=lines[i].second;
        double dx=b.first-a.first, dy= b.second-a.second;
        double seglen2 = dx*dx + dy*dy;
        f(j,0,m){
            P p=points[j];
            // robust check: distance from point to infinite line, and projection parameter t
            double cross = (p.first - a.first) * dy - (p.second - a.second) * dx;
            double seg_len = sqrt(seglen2);
            double dist_to_line = (seg_len < 1e-12) ? hypot(p.first - a.first, p.second - a.second) : fabs(cross) / seg_len;
            // tolerance chosen to tolerate rounding to 2 decimals (0.005 max shift) and numerical noise
            if(dist_to_line > 0.02) continue;
            double t = 0.0;
            if (seglen2 < 1e-12) {
                t = 0.0;
            } else {
                t = ((p.first - a.first) * dx + (p.second - a.second) * dy) / seglen2;
            }
            if (t + 1e-8 >= 0.0 && t <= 1.0 + 1e-8) {
                pts[i].push_back({t, j});
            }
        }
        sort(pts[i].begin(), pts[i].end(), [](const pair<double,int>&a,const pair<double,int>&b){
            if (fabs(a.first - b.first) > 1e-9) return a.first < b.first;
            return a.second < b.second;
        });
        pts[i].erase(unique(pts[i].begin(), pts[i].end(), [](auto &a, auto &b){ return a.second == b.second; }), pts[i].end());
    }
    vvi adj(m);
    f(i,0,n){
        auto &v = pts[i];
        f(k,1,sz(v)){
            int u = v[k-1].second;
            int w = v[k].second;
            if (u==w) continue;
            adj[u].push_back(w);
            adj[w].push_back(u);
        }
    }
    bool flag=false;
    f(i,0,m) if(!adj[i].empty()) { flag=true; break; }
    if(!flag){
        cout<<"Abandoned" << endl;
        return;
    }
    vector<int> deg(m,0);
    f(i,0,m){
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        deg[i] = sz(adj[i]);
    }
    queue<int> q;
    vector<char> poss(m,1);
    f(i,0,m){
        if (deg[i] < 2) { q.push(i); poss[i]=0; }
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v: adj[u]){
            if (poss[v]){
                deg[v]--;
                if (deg[v] < 2){
                    poss[v] = 0;
                    q.push(v);
                }
            }
        }
    }
    vi cycle;
    f(i,0,m) if(poss[i]) cycle.push_back(i);
    if (cycle.empty()){
        cout<<"Abandoned" << endl;
        return;
    }
    vvi adj2(m);
    f(u,0,m){
        if (!poss[u]) continue;
        for(int v: adj[u]) if (poss[v]) adj2[u].push_back(v);
    }
    int s = cycle[0];
    vi poly;
    poly.push_back(s);
    int curr = s;
    int prev = -1;
    if (adj2[curr].empty()) { cout<<"Abandoned" << endl; return; }
    int next = adj2[curr][0];
    prev = curr; curr = next;
    int cnt = 0;
    while(curr!=s && cnt<=m+5){
        poly.push_back(curr);
        int a = adj2[curr][0];
        int b = (adj2[curr].size() > 1) ? adj2[curr][1] : adj2[curr][0];
        int nxt = (a == prev) ? b : a;
        prev = curr;
        curr = nxt;
        cnt++;
    }
    if(curr!=s) {
        cout<<"Abandoned" << endl;
        return;
    }
    int k=sz(poly);
    if(k<3) { 
        cout<<"Abandoned" << endl; 
        return; 
    }

    // compute area via shoelace
    double area = 0.0;
    f(i,0,k){
        int j = (i+1)%k;
        P a = points[poly[i]];
        P b = points[poly[j]];
        area += a.first * b.second - b.first * a.second;
    }
    area = fabs(area) * 0.5;
    double u_len = 0.0;
    f(i,0,k){
        int j = (i+1)%k;
        P a = points[poly[i]];
        P b = points[poly[j]];
        u_len += dist(a,b);
    }
    double tot = 0.0;
    f(i,0,n){
        tot += dist(lines[i].first, lines[i].second);
    }
    double rem=tot-u_len;
    if(rem<0) rem = 0.0;
    double area2=(rem * rem)/(4.0*PI);
    if(area>area2) cout<<"Kalyan" << endl;
    else cout<<"Computer" << endl;
}

int32_t main() {
    fastio();
    int t = 1;
    while (t--) solve();
    return 0;
}
