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
PATTERN: Greedy Interval Scheduling (Sort by End Time)
Time Complexity: O(N log N) for sorting + O(N) for sweep = O(N log N)
Space Complexity: O(1) auxiliary (or O(log N) depending on internal sort memory)
=======================================================================================
Explanation:
- We define an `auto cmp` lambda to order the intervals strictly by their END times.
- We track the `prev_end` of the last valid meeting we decided to "attend".
- If the next meeting starts before `prev_end`, it's an overlap. Because we sorted 
  by end times, the one we already kept is mathematically guaranteed to be the better 
  choice (it ended earlier). So, we toss the current one (`removals++`).
- If it doesn't overlap, we accept the new meeting and update `prev_end`.
=======================================================================================
*/

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) return 0;
        
        // 1. Custom Comparator: Sort strictly by END times.
        // Capturing by reference `[&]` and using your `vii` macro for clean syntax.
        auto cmp = [&](const vii& a, const vii& b) -> bool {
            return a[1] < b[1]; 
        };
        
        // Apply the lambda to sort
        sort(all(intervals), cmp);
        
        int removals = 0;
        
        // 2. Initialize our baseline with the first meeting's end time
        int prev_end = intervals[0][1];
        
        for (int i = 1; i < n; i++) {
            
            // If the current meeting starts before the previous one finished...
            if (intervals[i][0] < prev_end) {
                // It's a conflict. Trash it.
                removals++;
            } 
            else {
                // No conflict! We attend this meeting and shift our timeline forward.
                prev_end = intervals[i][1];
            }
        }
        
        return removals;
    }
};