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
APPROACH 1: Recursive Backtracking (Take / Skip)
Time Complexity: O(N * 2^N) | Space Complexity: O(N) auxiliary stack
=======================================================================================
Explanation:
- We recursively build the subset array `v`.
- At every index `i`, we branch into two paths:
  1. Add `a[i]` to `v` and recurse.
  2. Remove `a[i]` from `v` (backtrack) and recurse without it.
- When `i == n`, we have evaluated all elements. We push the current state of `v` 
  into our answer.
=======================================================================================
*/
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& a) {
        int n = a.size();
        vvii ans;

        auto f = [&](int i, vii& v, auto && f) -> void {
            // BASE CASE: We reached the end of the array
            if(i == n) {
                ans.pb(v);
                return;
            }

            // PATH 1: Include the current element
            v.pb(a[i]);
            f(i + 1, v, f);
            
            // BACKTRACK: Undo the inclusion
            v.pop_back();

            // PATH 2: Exclude the current element
            f(i + 1, v, f);
        };

        vii v;
        f(0, v, f);
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 2: Bit Manipulation (Power Set)
Time Complexity: O(N * 2^N) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- There are exactly 2^N subsets. We can represent each subset as a binary number 
  from 0 to (2^N - 1).
- We loop through every number `mask`.
- We check every bit of `mask` from `0` to `n-1`. If the `i`-th bit is a `1`, we 
  include `a[i]` in the current subset.
- This entirely removes the overhead of the recursion stack!
=======================================================================================
*/
class Solution2 {
public:
    vector<vector<int>> subsets(vector<int>& a) {
        int n = a.size();
        vvii ans;
        
        // 1 << n is equivalent to 2^n
        int subsets_count = 1 << n; 
        
        // Loop from 000...0 to 111...1
        for (int mask = 0; mask < subsets_count; mask++) {
            vii v;
            
            // Check each bit of the current mask
            for (int i = 0; i < n; i++) {
                
                // If the i-th bit is set, include a[i]
                if (mask & (1 << i)) {
                    v.pb(a[i]);
                }
            }
            ans.pb(v);
        }
        
        return ans;
    }
};