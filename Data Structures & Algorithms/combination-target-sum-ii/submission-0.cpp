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
PATTERN: Recursive Backtracking with Pruning (Take / Skip)
Time Complexity: O(2^N) in the worst case | Space Complexity: O(N) auxiliary stack
=======================================================================================
Explanation:
- We sort the array to group duplicates together and enable early stopping.
- PRUNING: If `curr > t`, we stop exploring this branch immediately.
- TAKE: We add `a[i]` to our subset, add its value to `curr`, and recurse to `i + 1`.
- SKIP: We skip `a[i]`. To prevent generating duplicate combinations, we use a while 
  loop to jump over any adjacent numbers that share the exact same value as `a[i]`.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& a, int t) {
        int n = a.size();

        // 1. Sort to handle duplicates and enable pruning
        sort(all(a));

        vvii ans;

        auto f = [&](int i, int curr, vii& v, auto && f) -> void {
            
            // 2. Pruning: If the sum exceeds the target, kill this timeline
            if (curr > t) return;

            // 3. Base Case: We have processed all elements
            if (i == n) {
                if (curr == t) {
                    ans.pb(v);
                }
                return;
            }

            // ==========================================
            // PATH 1: Include the current element
            // ==========================================
            v.pb(a[i]);
            f(i + 1, curr + a[i], v, f);
            
            // Backtrack: Restore the bucket
            v.pop_back();

            // ==========================================
            // PATH 2: Exclude the current element
            // ==========================================
            // If we decide NOT to take a[i], taking a copy of a[i] in the very next 
            // step would create a duplicate combination. We must skip all copies!
            while (i + 1 < n && a[i] == a[i + 1]) {
                i++; 
            }
            
            f(i + 1, curr, v, f);
        };

        vii v;
        f(0, 0, v, f);

        return ans;
    }
};