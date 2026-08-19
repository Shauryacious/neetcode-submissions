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
APPROACH 1: Constrained Backtracking (Take / Skip string building)
Time Complexity: O(4^N / sqrt(N)) (Catalan Number) | Space: O(N) auxiliary stack
=======================================================================================
Explanation:
- We build the string character by character using our `s` bucket.
- We only place `(` if `open < n`.
- We only place `)` if `close < open`.
- This strictly prunes the recursion tree so no invalid strings are ever generated.
=======================================================================================
*/

class Solution {
public:
    vs generateParenthesis(int n) {
        vs ans;
        
        auto f = [&](int open, int close, string& s, auto && f) -> void {
            if (open == n && close == n) {
                ans.pb(s);
                return;
            }
            
            if (open < n) {
                s.pb('(');
                f(open + 1, close, s, f);
                s.pop_back();
            }
            
            if (close < open) {
                s.pb(')');
                f(open, close + 1, s, f);
                s.pop_back();
            }
        };
        
        string s = "";
        f(0, 0, s, f);
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 2: Catalan DP / Divide & Conquer (Top-Down Memoization)
Time Complexity: O(4^N / sqrt(N)) | Space: O(4^N / sqrt(N)) for the DP table
=======================================================================================
Explanation:
- Every valid string can be written as: "(" + left + ")" + right
- If the total pairs is `n`, we loop `i` from 0 to `n - 1`.
- `left` will have `i` pairs. `right` will have `n - 1 - i` pairs.
- We use a `dp` table (vector of vector of strings) to memoize the results for 
  smaller values of `n` so we never compute the same subproblem twice.
- Because the structural split guarantees uniqueness, no `set` is required!
=======================================================================================
*/

class Solution2 {
public:
    vs generateParenthesis(int n) {
        
        // dp[i] will store all valid combinations of 'i' pairs.
        // We use 'vs' (vector<string>) because uniqueness is mathematically guaranteed.
        vector<vs> dp(n + 1);
        
        // computed[i] acts as our O(1) check to see if dp[i] is already populated
        vector<bool> computed(n + 1, false);

        // Base case: 0 pairs is just an empty string
        dp[0] = {""};
        computed[0] = true;

        auto f = [&](int pairs, auto && f) -> vs {
            
            // If we already calculated the answer for this many pairs, return it immediately!
            if (computed[pairs]) return dp[pairs];

            vs current_ans;
            
            // Split the remaining (pairs - 1) between the inside and the outside
            for (int i = 0; i < pairs; i++) {
                
                // Get all valid strings for the left side (inside the brackets)
                vs lefts = f(i, f);
                
                // Get all valid strings for the right side (outside the brackets)
                vs rights = f(pairs - 1 - i, f);

                // Cartesian product: Combine every left with every right
                for (const string& l : lefts) {
                    for (const string& r : rights) {
                        current_ans.pb("(" + l + ")" + r);
                    }
                }
            }

            // Save the result to our DP table before returning
            dp[pairs] = current_ans;
            computed[pairs] = true;
            
            return current_ans;
        };

        return f(n, f);
    }
};