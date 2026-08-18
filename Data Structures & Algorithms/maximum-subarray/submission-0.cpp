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
DP PARADIGM: Top-Down Dynamic Programming (2D State - Chaining Mode)
=======================================================================================
Problem: LeetCode 53 - Maximum Subarray

Concept & State Definition:
- State: `f(i, started)` 
- `started == 0`: We have not started picking elements. We can skip or start.
- `started == 1`: We are actively chaining elements. We can extend or stop.

Base Cases:
- `i == n` and `started == 0`: Invalid! Subarray must have at least 1 element. Return -INF.
- `i == n` and `started == 1`: Valid end of array. Return 0.

Transition:
- CASE 1 (started == 0): 
  - `skip` = f(i + 1, 0)
  - `start` = nums[i] + f(i + 1, 1)
- CASE 2 (started == 1):
  - `extend` = nums[i] + f(i + 1, 1)
  - `stop` = 0 (We cut the array off here and take nothing further)
=======================================================================================
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        
        // DP array: n x 2. 
        // Initialized to -1e15 because answers can be negative (e.g., array of all -5s)
        // We cannot use -1 to represent 'uncomputed' here.
        vector<vector<ll>> dp(n + 5, vector<ll>(2, -1e15));

        auto f = [&](int i, int started, auto && f) -> ll {
            // Base Case: Reached the end of the array
            if (i == n) {
                if (started == 0) return -1e15; // Must pick at least one element
                else return 0; // Finished chaining elements safely
            }

            // Check memoization
            if (dp[i][started] != -1e15) return dp[i][started];

            ll ans = -1e15;

            if (started == 0) {
                // CASE 1: Hunting Mode (Not started yet)
                ll skip = f(i + 1, 0, f);
                ll start = nums[i] + f(i + 1, 1, f);
                
                ans = max(skip, start);
            } 
            else {
                // CASE 2: Chaining Mode (Actively building contiguous sequence)
                ll extend = nums[i] + f(i + 1, 1, f);
                ll stop = 0; // Cut the sequence here, take 0 points going forward
                
                ans = max(extend, stop);
            }

            return dp[i][started] = ans;
        };

        // Start at index 0, with 'started' flag = 0
        return f(0, 0, f);
    }
};