#include<bits/stdc++.h>
using namespace std;

int main() {
    // unlike leetcode you have to take complete input and print the output as well
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        // if there was an array given
        vector<int> a(n);
        for(auto& i:a) cin >> i;
        // or
        for (int i=0; i<n; i++){
            cin >> a[i];
        }

        // then your logic goes here

        // at last
        cout << "ans" // whatever you want to print whether it be  int or a string or a bool
        // depending on the problem
    }
}