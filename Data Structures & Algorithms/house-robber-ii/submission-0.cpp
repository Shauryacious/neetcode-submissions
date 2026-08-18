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
APPROACH 1: Top-Down DP with Domain Splitting (Index Boundaries)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
*/

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        
        // EDGE CASE TRAP: If there is only one house on the block, the circular 
        // logic doesn't apply. You just rob it and go home.
        if(n == 1) return nums[0]; 

        // STATE: dp[i] represents the max money we can rob starting from house 'i',
        // strictly up to the 'end_idx' boundary we set for the current universe.
        int dp[105];

        auto f = [&](int i, int end_idx, auto && f) -> int {
            
            // BASE CASE: If we cross the explicit boundary of our current universe,
            // there are no more houses we are legally allowed to rob.
            if(i > end_idx) return 0;

            // MEMOIZATION: Return cached result if we've already solved this subproblem.
            if(dp[i] != -1) return dp[i];

            // TRANSITION A (TAKE): 
            // Rob house 'i', trigger the alarm, skip 'i+1', evaluate from 'i+2'.
            int take = nums[i] + f(i + 2, end_idx, f);

            // TRANSITION B (SKIP): 
            // Ignore house 'i', don't trigger the alarm, evaluate freely from 'i+1'.
            int skip = f(i + 1, end_idx, f);

            // OPTIMAL CHOICE: Take the maximum of the parallel universes.
            return dp[i] = max(take, skip);
        };

        // ==================================================================
        // THE DOMAIN SPLIT: Handling the Circular Street
        // ==================================================================
        
        // UNIVERSE 1: Assume we might rob the FIRST house (index 0).
        // Consequence: We absolutely cannot touch the LAST house (index n-1).
        // Boundary: Evaluate from index 0 to index n-2.
        memset(dp, -1, sizeof(dp));
        int ans1 = f(0, n - 2, f);

        // UNIVERSE 2: Assume we might rob the LAST house (index n-1).
        // Consequence: We absolutely cannot touch the FIRST house (index 0).
        // Boundary: Evaluate from index 1 to index n-1.
        // NOTE: We MUST clear the DP array because the optimal answers change 
        // when the boundaries change!
        memset(dp, -1, sizeof(dp));
        int ans2 = f(1, n - 1, f);

        // The global maximum is simply the winner between the two universes.
        return max(ans1, ans2);
    }
};

/*
=======================================================================================
APPROACH 2: Bottom-Up DP (The Ultimate O(1) Space Solution)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
*/

class Solution2 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
        
        // HELPER LAMBDA: Runs the classic linear House Robber logic over a specific domain.
        auto robLinear = [&](int start_idx, int end_idx) -> int {
            
            // BASE CASES / INITIAL STATES:
            int prev2 = 0; // Tracks optimal loot from f(i - 2)
            int prev1 = 0; // Tracks optimal loot from f(i - 1)
            
            for (int i = start_idx; i <= end_idx; i++) {
                
                // TRANSITIONS: Take vs Skip
                int take = nums[i] + prev2;
                int skip = prev1;
                
                int current = max(take, skip);
                
                // SHIFT STATES FORWARD: Move pointers down the street
                prev2 = prev1;
                prev1 = current;
            }
            return prev1; // Holds the global max for this specific linear domain
        };
        
        // UNIVERSE 1: Rob from 0 to N-2
        int ans1 = robLinear(0, n - 2);
        
        // UNIVERSE 2: Rob from 1 to N-1
        int ans2 = robLinear(1, n - 1);
        
        return max(ans1, ans2);
    }
};