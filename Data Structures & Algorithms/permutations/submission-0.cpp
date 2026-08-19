// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<chrono>
#include<random>
#include<string>
#include<functional>
#include<iomanip>
#include<limits>
#include<array>
#include<utility>
#include<iterator>
#include<cstring>

using namespace std;

#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define all(x) (x).begin(), (x).end()
#define INF 1e9

/*
=======================================================================================
APPROACH 1: In-Place Swapping
Time Complexity: O(N * N!) 
  - There are N! permutations. For each, we do O(N) work to copy it to the answer.
Space Complexity: O(N) 
  - We do not use any extra arrays. The only extra space is the O(N) recursion stack.
=======================================================================================
Explanation:
- We use an integer `start` to track the current "slot" we are filling.
- We swap available numbers into this slot, recurse to fill the next slots, and 
  then backtrack by swapping them back to their original positions.
- PRO: Zero auxiliary memory used (highly optimized).
- CON: Destroys the original array ordering. It will NOT generate permutations in 
  lexicographical (dictionary) order.
=======================================================================================
*/

class Solution1 {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vvii ans;

        auto f = [&](int start, auto && f) -> void {
            if (start == n) {
                ans.pb(nums);
                return;
            }

            for (int i = start; i < n; i++) {
                // Lock nums[i] into the 'start' slot
                swap(nums[start], nums[i]);
                
                // Recurse to fill the remaining slots
                f(start + 1, f);
                
                // Backtrack to restore the array for the next iteration
                swap(nums[start], nums[i]);
            }
        };

        f(0, f);
        return ans;
    }
};

/*
=======================================================================================
APPROACH 2: Visited Array (The Ledger)
Time Complexity: O(N * N!)
  - Same as above, generating N! permutations and copying them takes O(N) time each.
Space Complexity: O(N)
  - We use O(N) for the recursion stack, O(N) for the `visited` array, and O(N) for `v`.
=======================================================================================
Explanation:
- We maintain a `visited` array to act as a ledger, tracking which numbers are 
  currently sitting in our `v` bucket.
- We ALWAYS scan the array from 0 to N-1. If a number is free (`!visited[i]`), we 
  take it, recurse, and then return it to the pool.
- PRO: If the input array is sorted, this mathematically guarantees the output 
  will be in strict lexicographical order.
- CON: Requires allocating additional memory for the ledger and the bucket.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vvii ans;
        
        vii v; 
        vii visited(n, 0); 

        auto f = [&](auto && f) -> void {
            if (v.size() == n) {
                ans.pb(v);
                return;
            }

            for (int i = 0; i < n; i++) {
                
                // If the number is free to use
                if (!visited[i]) {
                    
                    // TAKE
                    visited[i] = 1;
                    v.pb(nums[i]);
                    
                    // RECURSE
                    f(f);
                    
                    // BACKTRACK
                    v.pop_back();
                    visited[i] = 0;
                }
            }
        };

        f(f);
        return ans;
    }
};