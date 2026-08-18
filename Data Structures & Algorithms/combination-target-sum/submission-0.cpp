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
PATTERN: Backtracking (Take vs. Skip)
Time Complexity: O(2^T) loosely | Space Complexity: O(T / min_candidate) for recursion
=======================================================================================
Explanation:
- We explore every combination by deciding whether to take the current element or not.
- Because we can reuse elements, the "Take" branch recursively calls `i` (not `i + 1`).
- The "Skip" branch recursively calls `i + 1`.
- We use `v.pop_back()` to undo our state before taking the "Skip" branch.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& a, int t) {
        vvii ans;
        int n = a.size();
        
        // Lambda DFS with pass-by-reference array `v`
        auto f = [&](int i, int curr, vii& v, auto && f) -> void {
            
            // Base Case 1: Target achieved!
            if(curr == t) {
                ans.pb(v);
                return;
            }
            
            // Base Case 2: Out of bounds or sum exceeded
            if(i >= n || curr > t) {
                return;
            }
            
            // Choice 1: TAKE the current element
            // We push the element, and stay on index 'i' to allow infinite reuse
            v.pb(a[i]);
            f(i, curr + a[i], v, f);
            
            // THE BACKTRACK: Undo the choice to explore the other parallel universe
            v.pop_back();
            
            // Choice 2: SKIP the current element
            // We don't take it, and we permanently move to 'i + 1'
            f(i + 1, curr, v, f);
        };
        
        vii v;
        f(0, 0, v, f);
        
        return ans;
    }
};