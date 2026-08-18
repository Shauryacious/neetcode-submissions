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
APPROACH 1: Top-Down DP (Memoization) -> Your Exact Logic
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
Explanation:
- We use a recursive lambda `f(i)` to represent the number of ways to reach `n` from `i`.
- We cache the results in a `dp` array.
- If we hit `dp[i] != -1`, we instantly return the cached result, pruning the tree!
=======================================================================================
*/

class Solution {
public:
    int climbStairs(int n) {
        vii dp(n + 1, -1);

        auto f = [&](int i, auto && f) -> int {
            // Base Cases
            if(i == n) return 1;
            if(i > n) return 0;

            // Memoization Check
            if(dp[i] != -1) return dp[i];

            // Transitions: Take 1 step OR take 2 steps
            int ans = 0;
            ans += f(i + 1, f);
            ans += f(i + 2, f);

            return dp[i] = ans;
        };

        return f(0, f);
    }
};

/*
=======================================================================================
APPROACH 2: Space-Optimized Bottom-Up DP (The Fibonacci Shift)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
Explanation:
- Since step `i` only cares about `i-1` and `i-2`, we don't need an array.
- We just keep track of the `prev1` (1 step behind) and `prev2` (2 steps behind).
- In each iteration, the current step becomes `prev1 + prev2`, and we simply shift 
  our two pointers forward.
=======================================================================================
*/

class Solution2 {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int prev2 = 1; // Ways to reach step 1
        int prev1 = 2; // Ways to reach step 2
        
        for (int i = 3; i <= n; i++) {
            int current = prev1 + prev2;
            
            // Shift the pointers forward for the next iteration
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};