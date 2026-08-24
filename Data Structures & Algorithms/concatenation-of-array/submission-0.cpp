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
#define vvpii vector<vpii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define pll pair<ll, ll>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define all(x) (x).begin(), (x).end()
#define INF 1e18
#define ff first
#define ss second

/*
=======================================================================================
PATTERN: Array Traversal with Modulo Wrap-Around
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
Explanation:
- We initialize the `ans` vector with exactly `2 * n` size to avoid dynamic resizing.
- We loop from `0` to `2n - 1`.
- `i % n` guarantees that as soon as `i` reaches `n`, the index resets to `0`, 
  perfectly mapping the second half of `ans` to the original `nums` array.
=======================================================================================
*/

class Solution {
public:
    vector<int> getConcatenation(vector<int>& nums) {
        int n = nums.size();
        
        // Pre-allocate exactly 2*n memory for O(1) insertions
        vii ans(2 * n);
        
        for (int i = 0; i < 2 * n; i++) {
            // Modulo automatically handles the wrap-around
            ans[i] = nums[i % n];
        }
        
        return ans;
    }
};