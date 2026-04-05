#include<bits/stdc++.h>
using namespace std;
#define int long long
/*
    since constraints are low, and only contains lowercase letter we can you store all the
    available letters at a particular index say i, d must be divisor of n, that's the only 
    reasonable thing, for given constraint we can check all divisors and whichever smallest
    satisfies we pick a string for that particular. efficiently we can use maybe bit
*/
int32_t main(){
    int t; cin >> t;
    while(t--){
        int n,k; cin >> n >> k;
        vector<vector<bool>> tmp(n,vector<bool>(26,false));
        for(int i=0;i<k;i++){
            string s; cin >> s;
            for(int j=0;j<n;j++){
                tmp[j][s[j]-'a']=true;
            }
        }
        vector<int> div;
        for(int i=1;i*i<=n;i++){
            if(n%i==0){
                div.push_back(i);
                if(i!=n/i) div.push_back(n/i);
            }
        }
        sort(div.begin(),div.end());
        for(int x: div){
            string res = "";
            bool flag = true;
            for(int i=0;i<x;i++){
                int ch = -1;
                for(int c=0;c<26;c++){
                    bool flag2 = true;
                    for(int j=i; j<n; j+=x){
                        if(!tmp[j][c]){
                            flag2 = false;
                            break;
                        }
                    }
                    if(flag2){
                        ch = c; break;
                    }
                }
                if(ch!=-1){
                    res += (char)(ch+'a');
                }
                else{
                    flag = false; break;
                }
            }
            if(flag){
                string ans = "";
                for(int i=0;i<n/x;i++){
                    ans += res;
                }
                cout << ans << endl;
                break;
            }
        }

        
    }
}