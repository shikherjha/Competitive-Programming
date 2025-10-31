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
const long long INF = 1000000000000000000LL;

int mod_mul(int a, int b) { return ( (a % MOD) * (b % MOD) ) % MOD; }
int mod_pow(int a, long long b) {
    long long res = 1;
    long long x = a % MOD;
    while (b) {
        if (b & 1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        b >>= 1;
    }
    return (int)res;
}

vi sieve(int n){
    vector<char> isPrime(n+1, true);
    isPrime[0]=isPrime[1]=false;
    for (int i = 2; (long long)i*i <= n; i++) {
        if (isPrime[i]) {
            for (long long j = 1LL*i*i; j <= n; j += i) isPrime[(int)j] = 0;
        }
    }
    vi primes;
    for(int i=2;i<=n;i++) if(isPrime[i]) primes.push_back(i);
    return primes;
}

vector<int> primes;
const int maxi = 70;
int fact[maxi+1], invfact[maxi+1];

vpi helper(int n){
    vpi res;
    for(int p:primes){
        if((long long)p*(long long)p > n) break;
        if(n%p==0){
            int cnt = 0;
            while(n%p==0){ n /= p; cnt++; }
            res.emplace_back(p, cnt);
        }
    }
    if(n > 1) res.emplace_back(n, 1);
    return res;
}

int helper2(int n, int k){
    if(k==0) return 1;
    long long num = 1;
    long long m = n % MOD;
    for(int i=0;i<k;i++) num = (num * ((m + i) % MOD)) % MOD;
    num = (num * invfact[k]) % MOD;
    return (int)num;
}

int val = 1;
void solve() {
    int n, a, b; cin >> n >> a >> b;
    auto fac = helper(b);
    int m = (int)fac.size();
    vi primev(m);
    vi expo(m);
    f(i,0,m){ primev[i] = fac[i].first; expo[i] = fac[i].second; }
    vector<pair<long long, vector<int>>> divisors;
    function<void(int,long long,vector<int>&)> rec = [&](int idx, long long cur, vector<int>& curE){
        if(idx==m){ divisors.emplace_back(cur, curE); return; }
        long long p = primev[idx];
        long long v = cur;
        for(int e=0;e<=expo[idx];e++){
            curE.push_back(e);
            rec(idx+1, v, curE);
            curE.pop_back();
            if(e<expo[idx]) v = v * p;
        }
    };
    vector<int> tmp;
    rec(0, 1LL, tmp);
    int ans = 0;
    for(auto &dv: divisors){
        long long d = dv.first;
        if(d > a) continue;
        int ways = 1;
        for(int j=0;j<m;j++){
            int ej = expo[j];
            int x = dv.second[j];
            int left = helper2(n, x);
            int right = helper2(n, ej - x);
            ways = mod_mul(ways, left);
            ways = mod_mul(ways, right);
        }
        ans += ways;
        if(ans >= MOD) ans -= MOD;
    }
    cout << "Case #" << val++ << ": " << ans % MOD << endl;
}

int32_t main() {
    fastio();

#ifdef LOCAL
    freopen("inputf.in", "r", stdin);
    freopen("output.in", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    primes = sieve(10000000);
    fact[0]=1;
    f(i,1,maxi+1) fact[i] = (long long)fact[i-1]*i % MOD;
    invfact[maxi] = mod_pow(fact[maxi], MOD-2);
    for(int i=maxi;i>0;i--) invfact[i-1] = (long long)invfact[i]*i%MOD;

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
