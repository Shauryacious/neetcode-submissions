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

// Define Constants
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
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
APPROACH 1: Pre-computed Prefix/Suffix Arrays (Your Logic)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
Explanation:
- We compute an array `lmax` where `lmax[i]` is the tallest building from index 0 to i.
- We compute an array `rmax` where `rmax[i]` is the tallest building from index n-1 to i.
- For any building `i`, the water it traps is the minimum of its bounding walls minus
  its own physical height.
=======================================================================================
*/
class Solution1 {
public:
    int trap(vector<int>& heights) {
        int n = heights.size();
        if (n == 0) return 0;
        
        vll lmax(n, 0), rmax(n, 0);
        
        // Build prefix maximums (left to right)
        lmax[0] = heights[0];
        for (int i = 1; i < n; i++) {
            lmax[i] = max(lmax[i - 1], (ll)heights[i]);
        }
        
        // Build suffix maximums (right to left)
        rmax[n - 1] = heights[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rmax[i] = max(rmax[i + 1], (ll)heights[i]);
        }

        ll ans = 0;
        
        // Calculate physics for each column
        for (int i = 0; i < n; i++) {
            ans += min(lmax[i], rmax[i]) - heights[i];
        }

        return (int)ans;
    }
};

/*
=======================================================================================
APPROACH 2: Dynamic Two Pointers (The Optimal Interview Approach)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
Explanation:
- We use two pointers squeezing inward from the edges. 
- We track the maximum height seen on the left and the right so far.
- If `height[left] <= height[right]`, we know the right side is a massive wall. The 
  water at `left` is bottlenecked STRICTLY by `left_max`. We process `left` and move it.
- If `height[right] < height[left]`, we know the left side is a massive wall. The 
  water at `right` is bottlenecked STRICTLY by `right_max`. We process `right` and move it.
=======================================================================================
*/
class Solution {
public:
    int trap(vector<int>& heights) {
        int n = heights.size();
        if (n == 0) return 0;
        
        int left = 0, right = n - 1;
        int left_max = 0, right_max = 0;
        int ans = 0;
        
        while (left < right) {
            
            // The left wall is smaller, so it acts as the strict bottleneck
            if (heights[left] <= heights[right]) {
                
                // Have we found a new tallest left wall? Update it.
                if (heights[left] >= left_max) {
                    left_max = heights[left];
                } 
                // Otherwise, calculate how much water this valley traps
                else {
                    ans += left_max - heights[left];
                }
                left++;
            } 
            
            // The right wall is smaller, so it acts as the strict bottleneck
            else {
                
                // Have we found a new tallest right wall? Update it.
                if (heights[right] >= right_max) {
                    right_max = heights[right];
                } 
                // Otherwise, calculate how much water this valley traps
                else {
                    ans += right_max - heights[right];
                }
                right--;
            }
        }
        
        return ans;
    }
};