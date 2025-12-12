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
const int MAX = 1e9;

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

// Intuition:
    // Since the constraints seems low we can simulate the process
    // One thing to notice in either of the ops (H or V) the loose somepart in the down face and
    // overlap some part from the down face in the up face
    // lets say we have vx op-> in that everything will over (0 to x-1) from the down face (x to n)
    // this will go on, we can keep track of both the faces and maybe keep on simulating the process
    // to get the final answer
    // for the down face, it will loose items it will never get overlapped from thing from the up face



void solve() {
    int n, m; cin >> n >> m;

    vector<string> str;
    string s;
    while (cin >> s) str.push_back(s);

    map<pair<int,int>, vi> mp;
    int val = 1;
    f(i,0,n){
        f(j,0,m){
            mp[make_pair(i,j)]=vi(1, val++);
        }
    }

    int min_r =0, max_r=n - 1, min_c=0, max_c=m - 1;
    for(auto i =0;i<sz(str);i++){
        string it=str[i];
        char t=tolower(it[0]);
        int k=(int)stoll(it.substr(1));
        map<pair<int,int>, vi> newmp;
        vector<pair<pair<int,int>, vi>> entries;
        entries.reserve(mp.size());
        for(auto &e: mp) entries.push_back(e);

        if(t=='v') {
            int cols= max_c-min_c+1;
            int p=cols-k;
            double fold=min_c+p-0.5;

            vector<pair<pair<int,int>, vi>> base, f;
            base.reserve(entries.size());
            f.reserve(entries.size());
            for(auto &e: entries){
                int r = e.first.first;
                int c = e.first.second;
                if(c>fold) f.push_back(e);
                else base.push_back(e);
            }

            sort(base.begin(), base.end(), [](auto &A, auto &B){
                if (A.first.first != B.first.first) return A.first.first < B.first.first;
                return A.first.second < B.first.second;
            });
            for(auto &e: base){
                auto pos = e.first; vi st = e.second;
                if (newmp.count(pos)) {
                    vi tmp=newmp[pos];
                    tmp.insert(tmp.end(), st.begin(), st.end());
                    newmp[pos]=tmp;
                } else newmp[pos]=st;
            }

            sort(f.begin(), f.end(), [](auto &A, auto &B){
                if (A.first.first != B.first.first) return A.first.first < B.first.first;
                return A.first.second > B.first.second;
            });
            for(auto &e: f){
                int r = e.first.first;
                int c = e.first.second;
                vi st = e.second;
                int newc=(int)floor(2.0*fold-c+MIN);
                pair<int,int> pos = make_pair(r, newc);
                vi srev(st.rbegin(), st.rend());
                if(newmp.count(pos)) {
                    vi tmp = srev;
                    tmp.insert(tmp.end(), newmp[pos].begin(), newmp[pos].end());
                    newmp[pos] = tmp;
                } else {
                    newmp[pos] = srev;
                }
            }
        }
        else if(t=='h') {
            int rows =max_r -min_r+ 1;
            int p = k;
            double fold=min_r+p-0.5;

            vector<pair<pair<int,int>, vi>> base, f;
            base.reserve(entries.size());
            f.reserve(entries.size());
            for(auto &e: entries){
                int r = e.first.first;
                int c = e.first.second;
                if(r>fold) f.push_back(e);
                else base.push_back(e);
            }

            sort(base.begin(), base.end(), [](auto &A, auto &B){
                if (A.first.first != B.first.first) return A.first.first < B.first.first;
                return A.first.second < B.first.second;
            });
            for(auto &e: base){
                auto pos = e.first; vi st = e.second;
                if (newmp.count(pos)) {
                    vi tmp=newmp[pos];
                    tmp.insert(tmp.end(), st.begin(), st.end());
                    newmp[pos]=tmp;
                } else newmp[pos]=st;
            }

            sort(f.begin(), f.end(), [](auto &A, auto &B){
                if (A.first.second != B.first.second) return A.first.second < B.first.second;
                return A.first.first > B.first.first;
            });
            for(auto &e: f){
                int r = e.first.first;
                int c = e.first.second;
                vi st = e.second;
                int newr= (int)floor(2.0 *fold-r+MIN);
                pair<int,int> pos = make_pair(newr, c);
                vi srev(st.rbegin(), st.rend());
                if (newmp.count(pos)) {
                    vi tmp = srev;
                    tmp.insert(tmp.end(), newmp[pos].begin(), newmp[pos].end());
                    newmp[pos] =tmp;
                } else {
                    newmp[pos]=srev;
                }
            }
        }

        int new_min_r=INT_MAX, new_max_r=INT_MIN, new_min_c=INT_MAX, new_max_c=INT_MIN;
        for(auto it1 =newmp.begin();it1!= newmp.end();it1++){
            int r = it1->first.first;
            int c = it1->first.second;
            new_min_r=  min(new_min_r,r);
            new_max_r= max(new_max_r,r);
            new_min_c= min(new_min_c,c);
            new_max_c = max(new_max_c,c);
        }
        if(!newmp.empty()){
            min_r =new_min_r; max_r=new_max_r;
            min_c=new_min_c; max_c=new_max_c;
        }
        mp.swap(newmp);
    }

        auto it =mp.end();
        for(auto it1=mp.begin();it1!=mp.end();it1++) {
            if(it ==mp.end() || it1->second.size() >it->second.size())
                it=it1;
        }

        if(it != mp.end() && !it->second.empty()) {
            vi &ans=it->second;
            cout << ans.front() << ' ' << ans.back() << endl;
        } 
        else{
            cout << '0' << ' ' << '0' << endl;
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
    while (t--) solve();

    return 0;
}
