// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
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
APPROACH 1: Top-Down DP (Memoization)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
*/

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        
        // STATE: dp[i] represents the maximum amount of money you can rob 
        // starting strictly from house 'i' and looking at all remaining houses to the right.
        vii dp(n, -1);

        auto f = [&](int i, auto && f) -> int {
            // BASE CASE: If we have moved past the last house (i >= n), 
            // there are no more houses to rob, yielding 0 money.
            if(i >= n) return 0;

            // MEMOIZATION: If we already solved this exact subproblem, return the cached answer.
            if(dp[i] != -1) return dp[i];

            // TRANSITION A (TAKE): 
            // We rob house 'i', gaining nums[i]. The alarm forces us to skip 'i + 1'.
            // The next valid state we can evaluate is 'i + 2'.
            int take = nums[i] + f(i + 2, f);

            // TRANSITION B (SKIP): 
            // We do NOT rob house 'i', gaining 0. The alarm is not triggered, 
            // leaving us completely free to evaluate the very next house at 'i + 1'.
            int skip = f(i + 1, f);

            // OPTIMAL CHOICE: Take the maximum of the parallel universes.
            return dp[i] = max(take, skip);
        };

        // We want the maximum money starting our evaluation at house 0.
        return f(0, f);
    }
};

/*
=======================================================================================
APPROACH 2: Bottom-Up DP (O(1) Space Optimization)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
*/

class Solution2 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        
        // BASE CASES / INITIAL STATES:
        // prev2 tracks the optimal answer for f(i - 2)
        // prev1 tracks the optimal answer for f(i - 1)
        int prev2 = 0; 
        int prev1 = 0; 
        
        for (int i = 0; i < n; i++) {
            
            // TRANSITIONS:
            // Take the current house (nums[i]) and add the optimal loot from (i - 2).
            int take = nums[i] + prev2;
            
            // Skip the current house and carry forward the optimal loot from (i - 1).
            int skip = prev1;
            
            // The state for the current house 'i'
            int current = max(take, skip);
            
            // SHIFT STATES FORWARD:
            // What was (i - 1) now becomes (i - 2) for the next iteration.
            // What was current 'i' now becomes (i - 1) for the next iteration.
            prev2 = prev1;
            prev1 = current;
        }
        
        // At the end of the loop, prev1 holds the global maximum for the entire street.
        return prev1;
    }
};