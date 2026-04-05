#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Function to query the interactor
int query(int l, int r) {
    if (l > r) return 0;
    cout << "? " << l << " " << r << endl;
    int ans;
    cin >> ans;
    return ans;
}

// Calculate number of subarrays containing the current set of required numbers
// by subtracting subarrays that fall completely inside "gaps"
long long count_valid_subarrays(int n, const set<int>& pos) {
    long long total_subarrays = (long long)n * (n + 1) / 2;
    long long invalid_subarrays = 0;
    
    int prev = 0; // Virtual boundary at 0
    for (int p : pos) {
        long long len = p - prev - 1;
        if (len > 0) {
            invalid_subarrays += len * (len + 1) / 2;
        }
        prev = p;
    }
    // Last gap from last position to n
    long long len = n - prev;
    if (len > 0) {
        invalid_subarrays += len * (len + 1) / 2;
    }
    
    return total_subarrays - invalid_subarrays;
}

void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;

    // Step 1: Find all zeros
    set<int> pos;
    for (int i = 1; i <= n; ++i) {
        if (query(i, i) == 1) { // MEX of {0} is 1
            pos.insert(i);
        }
    }

    // Special Case: No zeros found
    if (pos.empty()) {
        if (k == 0) cout << "! " << (long long)n * (n + 1) / 2 << endl;
        else cout << "! 0" << endl;
        return;
    }

    // Special Case: k=0
    if (k == 0) {
        long long ans = (long long)n * (n + 1) / 2 - count_valid_subarrays(n, pos);
        cout << "! " << ans << endl;
        return;
    }

    long long count_ge_k = 0;

    // We proceed to find relevant positions for v = 1 to k
    for (int v = 1; v <= k; ++v) {
        // If v == k, 'pos' currently contains critical indices for 0..k-1.
        // This is exactly what we need to calculate N(k).
        if (v == k) {
            count_ge_k = count_valid_subarrays(n, pos);
        }

        set<int> new_occurrences;
        
        // Create a list of boundaries including 0 and n+1 for iteration
        vector<int> bounds;
        bounds.push_back(0);
        for(int p : pos) bounds.push_back(p);
        bounds.push_back(n + 1);

        for (size_t i = 0; i < bounds.size() - 1; ++i) {
            // Define the range of the current gap
            int gap_l = bounds[i];
            int gap_r = bounds[i+1];
            
            // The query range must span the gap boundaries to check for connectivity
            // Left boundary of query
            int q_l = (gap_l == 0) ? 1 : gap_l; 
            // Right boundary of query
            int q_r = (gap_r == n + 1) ? n : gap_r;

            if (q_l >= q_r) continue;

            // Check if value 'v' exists in this gap context
            if (query(q_l, q_r) > v) {
                // v exists in [q_l, q_r] (considering the context of existing boundaries)
                
                // Case 1: Leftmost gap (0 to first pos)
                if (gap_l == 0) {
                    // Find the rightmost v in this gap (closest to q_r)
                    int L = 1, R = q_r - 1;
                    int idx = -1;
                    while (L <= R) {
                        int mid = L + (R - L) / 2;
                        if (query(mid, q_r) > v) {
                            idx = mid;
                            L = mid + 1; // Look for a later index
                        } else {
                            R = mid - 1;
                        }
                    }
                    if (idx != -1) new_occurrences.insert(idx);
                }
                // Case 2: Rightmost gap (last pos to n)
                else if (gap_r == n + 1) {
                    // Find the leftmost v in this gap (closest to q_l)
                    int L = q_l + 1, R = n;
                    int idx = -1;
                    while (L <= R) {
                        int mid = L + (R - L) / 2;
                        if (query(q_l, mid) > v) {
                            idx = mid;
                            R = mid - 1; // Look for an earlier index
                        } else {
                            L = mid + 1;
                        }
                    }
                    if (idx != -1) new_occurrences.insert(idx);
                }
                // Case 3: Middle gap (between two existing values)
                else {
                    // Find leftmost v (closest to q_l)
                    int L = q_l + 1, R = q_r - 1;
                    int left_idx = -1;
                    while (L <= R) {
                        int mid = L + (R - L) / 2;
                        if (query(q_l, mid) > v) {
                            left_idx = mid;
                            R = mid - 1;
                        } else {
                            L = mid + 1;
                        }
                    }
                    if (left_idx != -1) new_occurrences.insert(left_idx);

                    // Find rightmost v (closest to q_r)
                    L = q_l + 1; R = q_r - 1;
                    int right_idx = -1;
                    while (L <= R) {
                        int mid = L + (R - L) / 2;
                        if (query(mid, q_r) > v) {
                            right_idx = mid;
                            L = mid + 1;
                        } else {
                            R = mid - 1;
                        }
                    }
                    if (right_idx != -1) new_occurrences.insert(right_idx);
                }
            }
        }
        // Update pos with new findings
        pos.insert(new_occurrences.begin(), new_occurrences.end());
    }

    // After loop, pos contains critical indices for 0..k
    // This allows calculating N(k+1)
    long long count_ge_k_plus_1 = count_valid_subarrays(n, pos);

    // Answer is N(k) - N(k+1)
    cout << "! " << count_ge_k - count_ge_k_plus_1 << endl;
}

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}