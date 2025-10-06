#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define vi vector<int>
#define f(i,a,b) for (int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define endl '\n'
 
#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
 
const int INF = 1000000000000000000LL;
 
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
        else if(price[i] == dp2[i]){
            // This station is the most expensive among the remaining.
            // If we can reach the next station with current fuel, do nothing.
            // Otherwise, buy just enough fuel to reach the next station.
            if(curr_fuel < need){
                int buy = need - curr_fuel;
                buy = min(buy, c - curr_fuel);
                if(buy * price[i] > m) buy = m / price[i];
                curr_fuel += buy;
                m -= buy * price[i];
            }
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
 
int32_t main(){
    fastio();
 
#ifdef LOCAL
    freopen("inputf.in", "r", stdin);
    freopen("output.in", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
 
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}