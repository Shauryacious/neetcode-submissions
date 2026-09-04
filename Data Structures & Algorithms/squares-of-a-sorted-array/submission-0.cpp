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
#define INF 1e9 
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
SOLUTION 1: Brute Force (Square and Sort)
Time Complexity: O(N log N) | Space Complexity: O(1) auxiliary space (excluding output)
=======================================================================================
EXPLANATION OF LOGIC:
1. Traverse the array and replace every element with its square.
2. Call std::sort on the entire array.
3. This is trivial but ignores the fact that the original array was already sorted.
=======================================================================================
*/

class Solution1 {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ans = nums;
        
        for (int i = 0; i < sz(ans); i++) {
            ans[i] = ans[i] * ans[i];
        }
        
        sort(all(ans));
        return ans;
    }
};

/*
=======================================================================================
SOLUTION 2: Optimal (Backwards Two-Pointer)
Time Complexity: O(N) | Space Complexity: O(1) auxiliary space (excluding output)
=======================================================================================
EXPLANATION OF LOGIC:
1. Initialize `left` at 0 and `right` at `N - 1`.
2. Initialize `k` at the end of the `ans` array to fill it backwards.
3. Compare the squares of `nums[left]` and `nums[right]`.
4. The larger square represents the "extreme edge". We place it at `ans[k]`, 
   decrement `k`, and move the corresponding pointer inward.
5. The loop strictly stops when `left` and `right` cross.
=======================================================================================
*/

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = sz(nums);
        vector<int> ans(n);
        
        int left = 0;
        int right = n - 1;
        int k = n - 1; // Anchor to fill the answer array backwards
        
        while (left <= right) {
            // Extract the squares cleanly
            int sq_left = nums[left] * nums[left];
            int sq_right = nums[right] * nums[right];
            
            // The largest square goes to the very end of the remaining buffer
            if (sq_left > sq_right) {
                ans[k] = sq_left;
                left++;
            } 
            else {
                ans[k] = sq_right;
                right--;
            }
            
            // Advance the placement anchor
            k--;
        }
        
        return ans;
    }
};