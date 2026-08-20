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

// Define Constants & Macros
#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e9 // Using 1e9 to avoid overflow during addition
#define nl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define py cout<<"YES"<<nl
#define pn cout<<"NO"<<nl
#define pm cout<<"-1"<<nl
#define all(x) (x).begin(), (x).end()

// Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<pll> vpll;

#define vvpll vector<vpll>

/*
=======================================================================================
SOLUTION 1: Top-Down Dynamic Programming (Memoization)
Time Complexity: O(N^2) | Space Complexity: O(N) auxiliary
=======================================================================================
Intuition & Logic:
- We want to explore all possible jump paths and find the one with the minimum cost.
- State: `dp[i]` caches the minimum jumps required to reach the last index from `i`.
- Base Case: If `i >= n - 1`, we are already at the destination (0 jumps needed).
- Transition: If we are at index `i`, we can jump anywhere from 1 to `nums[i]` steps.
  We ask our recursive function: "What is the cost to finish the game from `i + step`?"
  We add 1 to that answer (for the jump we just made) and track the minimum.
=======================================================================================
*/

class Solution1 {
public:
    int jump(vector<int>& nums) {
        int n = sz(nums);
        
        // dp[i] stores min jumps to reach the end from index i
        vii dp(n, -1);
        
        auto f = [&](int i, auto && f) -> int {
            // Base Case: Reached or passed the last index
            if (i >= n - 1) {
                return 0;
            }
            
            // Return cached result
            if (dp[i] != -1) {
                return dp[i];
            }
            
            int mini = INF;
            
            // Try every possible jump from the current index
            for (int step = 1; step <= nums[i]; step++) {
                // +1 for the current jump, plus the optimal jumps from the landing spot
                int jumps = 1 + f(i + step, f);
                mini = min(mini, jumps);
            }
            
            return dp[i] = mini;
        };
        
        return f(0, f);
    }
};


/*
=======================================================================================
SOLUTION 2: Greedy (Expanding Windows / BFS)
Time Complexity: O(N) strictly one pass | Space Complexity: O(1) auxiliary
=======================================================================================
Intuition & Logic:
- Instead of exploring every individual path, we group our reachable positions into "windows".
- Imagine you make a jump. That jump gives you a range of indices you can now reach.
  This range is your `curr_window_end`.
- As you walk through the indices in your current window, you are scouting the future: 
  "If I were to jump from here, what is the absolute `farthest` index I could reach?"
- The exact moment you step out of your current window (`i == curr_window_end`), you 
  are forced to commit to a new jump to keep moving forward.
- You increment your jump counter and shift your window to the `farthest` boundary you 
  discovered. You collapse an O(N^2) pathfinding mission into a brilliant O(N) sweep!
=======================================================================================
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = sz(nums);
        
        // Edge case: If array size is 1, we are already at the destination
        if (n <= 1) return 0;
        
        int jumps = 0;
        int curr_window_end = 0;
        int farthest = 0;
        
        // We do not need to process the last index because we just want to reach it
        for (int i = 0; i < n - 1; i++) {
            
            // Constantly calculate the maximum reach from the current position
            farthest = max(farthest, i + nums[i]);
            
            // If we have reached the end of the current jump's coverage window
            if (i == curr_window_end) {
                jumps++;                       // We must make a jump to cross the boundary
                curr_window_end = farthest;    // Shift the boundary to the furthest reachable point
                
                // Early exit optimization: If our new window reaches the end, we can stop
                if (curr_window_end >= n - 1) {
                    break;
                }
            }
        }
        
        return jumps;
    }
};