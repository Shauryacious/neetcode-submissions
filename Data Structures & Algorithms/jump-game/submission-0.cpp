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
PATTERN: Greedy (Tracking the Maximum Boundary)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
Explanation:
- We maintain a single variable, `max_reach`, which represents the furthest index 
  we have the "fuel" to reach.
- As we iterate through the array, we check two things:
  1. Are we stuck? If `i > max_reach`, we hit a gap we couldn't cross.
  2. Can we extend our reach? `max(max_reach, i + nums[i])`.
- If `max_reach` ever touches or exceeds the last index, we instantly win.
=======================================================================================
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        
        // EDGE CASE: If the array only has 1 element, you are already at the end.
        if (n == 1) return true;
        
        // STATE: Tracks the absolute furthest index we have the power to reach.
        int max_reach = 0;
        
        for (int i = 0; i < n; i++) {
            
            // THE FAILURE CONDITION: 
            // We physically stepped onto an index that is beyond our maximum jump power.
            // This means we hit a '0' previously and got stranded.
            if (i > max_reach) {
                return false;
            }
            
            // THE GREEDY TRANSITION: 
            // From our current spot 'i', our jump power is 'nums[i]'. 
            // So we can reach index 'i + nums[i]'. Does this beat our previous record?
            max_reach = max(max_reach, i + nums[i]);
            
            // EARLY EXIT (OPTIMIZATION):
            // If our flashlight already illuminates the end of the array (or beyond),
            // there is no need to keep calculating. We won.
            if (max_reach >= n - 1) {
                return true;
            }
        }
        
        return true;
    }
};