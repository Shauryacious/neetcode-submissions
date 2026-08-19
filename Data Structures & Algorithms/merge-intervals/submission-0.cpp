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
PATTERN: Sorting + Array Expansion
Time Complexity: O(N log N) for sorting + O(N) for sweep = O(N log N)
Space Complexity: O(1) auxiliary (excluding the output array)
=======================================================================================
Explanation:
- We sort the intervals so that overlaps are physically adjacent.
- We maintain the "active" merged interval at the back of our `ans` array.
- For each new interval, if its start time is <= the active interval's end time, 
  they overlap. We update the active interval's end time to the maximum of both.
- If it doesn't overlap, we simply push it into `ans` as the new active interval.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) return intervals;
        
        // 1. Sort the intervals by their start times
        // C++ automatically sorts vector of vectors by the first element, then the second.
        sort(all(intervals));
        
        vvii ans;
        
        // 2. Put the first interval into the answer array to serve as our baseline
        ans.pb(intervals[0]);
        
        for (int i = 1; i < n; i++) {
            
            // `ans.back()` always holds our currently active, expanding interval
            // If the current interval starts before or exactly when the active one ends...
            if (intervals[i][0] <= ans.back()[1]) {
                
                // MERGE: Update the end time of the active interval
                ans.back()[1] = max(ans.back()[1], intervals[i][1]);
                
            } else {
                
                // NO OVERLAP: Push the new interval into the answer array. 
                // It now becomes the new baseline we compare against.
                ans.pb(intervals[i]);
                
            }
        }
        
        return ans;
    }
};