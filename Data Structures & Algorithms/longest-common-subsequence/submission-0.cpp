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
APPROACH 1: Top-Down Dynamic Programming (Memoization)
Time Complexity: O(N * M) | Space Complexity: O(N * M)
=======================================================================================
*/
class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();

        // 2D DP Table to cache states. 
        int dp[1001][1001];
        memset(dp, -1, sizeof(dp));

        auto f = [&](int i, int j, auto && f) -> int {
            // BASE CASE: Out of bounds means 0 matching characters left.
            if(i >= n || j >= m) return 0;

            // MEMOIZATION: Return cached subproblem result.
            if(dp[i][j] != -1) return dp[i][j];

            int ans = 0;

            // TRANSITION A: Characters match! Claim 1 point and move both pointers.
            if(s1[i] == s2[j]) {
                ans = max(ans, 1 + f(i + 1, j + 1, f));
            } 
            // TRANSITION B: Mismatch. Branch out and take the max of dropping s1[i] OR s2[j].
            else {
                int skip_s1 = f(i + 1, j, f);
                int skip_s2 = f(i, j + 1, f);
                ans = max(skip_s1, skip_s2);
            }
            
            return dp[i][j] = ans;
        };

        return f(0, 0, f);
    }
};

/*
=======================================================================================
APPROACH 2: Bottom-Up Dynamic Programming (Space Optimized 2-Row Trick)
Time Complexity: O(N * M) | Space Complexity: O(M) 
=======================================================================================
Explanation:
- We build the matrix iteratively from the bottom right to the top left.
- Because `row[i]` ONLY depends on `row[i+1]`, we don't need a full N x M grid.
- We maintain `next_row` (which acts as row i+1) and `curr_row` (which acts as row i).
- After filling `curr_row`, we shift it down to become `next_row` for the next loop!
=======================================================================================
*/
class Solution2 {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        
        // Instead of a 1000x1000 grid, we only need two rows of size (m + 1).
        // Initialized to 0, which perfectly acts as our out-of-bounds Base Case!
        vii next_row(m + 1, 0);
        vii curr_row(m + 1, 0);

        // Build from bottom-up (right-to-left) to mimic the recursive tree
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                
                if (s1[i] == s2[j]) {
                    // 1 + f(i+1, j+1)
                    curr_row[j] = 1 + next_row[j + 1];
                } else {
                    // max(f(i+1, j), f(i, j+1))
                    curr_row[j] = max(next_row[j], curr_row[j + 1]);
                }
            }
            // Shift the state forward: current row becomes the next row we look back on
            next_row = curr_row;
        }

        // The answer for f(0, 0) bubbles up to the front of the next_row
        return next_row[0];
    }
};