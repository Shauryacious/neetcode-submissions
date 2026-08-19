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
PATTERN: Recursive Backtracking (Duplicate Skipping)
Time Complexity: O(N * 2^N) | Space Complexity: O(N) auxiliary stack
=======================================================================================
Explanation:
- We SORT the array so all identical elements are adjacent.
- We branch into two paths at every index:
  1. TAKE: We include `a[i]` and move to `i + 1`. We do NOT skip duplicates here 
     because multiple identical elements can exist within the same valid subset.
  2. SKIP: We exclude `a[i]`. To prevent generating parallel universes that look 
     identical, we fast-forward `i` past all elements that equal `a[i]`.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& a) {
        int n = a.size();
        
        // 1. Sort to group duplicates together
        sort(all(a));
        
        vvii ans;

        auto f = [&](int i, vii& v, auto && f) -> void {
            
            // Base Case: We evaluated all positions
            if (i == n) {
                ans.pb(v);
                return;
            }

            // ==========================================
            // PATH 1: Include the current element
            // ==========================================
            v.pb(a[i]);
            f(i + 1, v, f);
            
            // Backtrack
            v.pop_back();

            // ==========================================
            // PATH 2: Exclude the current element
            // ==========================================
            // If we skip this value, we must skip ALL copies of this value 
            // to avoid generating duplicate subsets!
            while (i + 1 < n && a[i] == a[i + 1]) {
                i++;
            }
            
            f(i + 1, v, f);
        };

        vii v;
        f(0, v, f);
        
        return ans;
    }
};