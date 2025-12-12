
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define f(i,a,b) for(int i=a;i<b;i++)

int helper(vector<int>& a){
    int n = a.size();
    a.push_back(0);
    int maxArea = 0;
    stack<int> st;
    for(int i=0;i<n+1;i++){
        //if(!st.empty())  cout << a[i] << ' ' << a[st.top()] << endl;
        while(!st.empty() && a[i]<a[st.top()]){
            int idx = st.top(); st.pop();
            int h = a[idx];
            int w = ((st.empty())? i:i-st.top()-1);
            //cout << h << ' ' << w << endl;
            maxArea = max(maxArea,h*w);
        }
        st.push(i);
    }

    a.pop_back();
    //cout  << maxArea << endl;
    return maxArea;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    #ifdef LOCAL
        freopen("inputf.in", "r", stdin);
        freopen("output.in", "w", stdout);
        freopen("error.txt", "w", stderr);
    #endif

    int t; cin >> t;
    while(t--){
        int n,m; cin >> n >> m;
        vector<string> a(n),b(n);
        vector<vector<int>>grid(n,vector<int>(m));
        for(int i=0; i<n; i++){
            cin >> a[i];
        }
        for(int i=0; i<n; i++){
            cin >> b[i];
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                grid[i][j] = ((a[i][j]==b[i][j])?1:0);
            }
        }
        /*for(int i=0; i<n; i++){
            cout << a[i] << endl;
        }
        cout << endl;
        
        for(int i=0; i<n; i++){
           cout << b[i] << endl; }
        cout << endl;
        
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                cout << grid[i][j] << ' ';
            }
            cout << endl;
        }*/
        
        vector<int> tmp(m,0);
        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                tmp[j] = ((grid[i][j]==0)? 0:tmp[j]+1);
            }
            // for(int x:tmp) cout << x << ' ' ;
            // cout << endl;
            ans = max(ans,helper(tmp));
        }
        cout << ans << "\n" ;
    }
    return 0;
}
