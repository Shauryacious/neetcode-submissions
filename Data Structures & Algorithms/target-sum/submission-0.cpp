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

class Solution {
    // DP Array: [current index][current sum + OFFSET]
    // Constraints: n <= 20, max sum is 1000, min sum is -1000.
    // So sum + offset will range from 0 to 2000.
    int dp[25][2005];
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        memset(dp, -1, sizeof(dp));
        
        int offset = 1000;

        // STATE DEFINITION:
        // i -> current index we are deciding on
        // curr_sum -> the accumulated sum so far
        auto f = [&](int i, int curr_sum, auto&& f) -> int {
            // Base case: Reached the end of the array
            if (i == n) {
                // If we hit the target, this path is valid (return 1 way)
                // Otherwise, invalid (return 0 ways)
                if (curr_sum == target) return 1;
                else return 0;
            }

            // Check memoization using the offset to prevent negative indices
            if (dp[i][curr_sum + offset] != -1) return dp[i][curr_sum + offset];

            // Choice 1: Add the current number
            int add = f(i + 1, curr_sum + nums[i], f);
            
            // Choice 2: Subtract the current number
            int sub = f(i + 1, curr_sum - nums[i], f);

            // Total ways is the sum of both valid paths
            return dp[i][curr_sum + offset] = add + sub;
        };

        // Start at index 0 with an accumulated sum of 0
        return f(0, 0, f);
    }
};