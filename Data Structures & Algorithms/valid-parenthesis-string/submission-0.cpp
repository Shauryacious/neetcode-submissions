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
SOLUTION 1: Dynamic Programming (Memoization)
Time Complexity: O(N^2) | Space Complexity: O(N^2) auxiliary for DP table
=======================================================================================
Explanation:
- `dp[i][open]` caches whether a valid string can be formed starting from index `i` 
  with `open` unmatched left brackets currently active.
- `open` can never exceed `n`, bounding our 2D DP array.
=======================================================================================
*/

class Solution {
public:
    bool checkValidString(string s) {
        int n = sz(s);
        
        // DP table: dp[index][open_count]
        vvii dp(n, vii(n + 1, -1));
        
        auto f = [&](int i, int open, auto && f) -> int {
            
            // Invalid path: more closing brackets than open ones
            if (open < 0) return 0;
            
            // Base Case: Reached the end. Valid only if all brackets are closed.
            if (i == n) return open == 0;
            
            if (dp[i][open] != -1) return dp[i][open];
            
            if (s[i] == '(') {
                return dp[i][open] = f(i + 1, open + 1, f);
            } 
            else if (s[i] == ')') {
                return dp[i][open] = f(i + 1, open - 1, f);
            } 
            else {
                // If it's '*', try all three possibilities: '(', ')', or empty string
                bool op1 = f(i + 1, open + 1, f);
                bool op2 = f(i + 1, open - 1, f);
                bool op3 = f(i + 1, open, f);
                
                return dp[i][open] = (op1 || op2 || op3);
            }
        };
        
        return f(0, 0, f);
    }
};




/*
=======================================================================================
SOLUTION 2: Two Stacks (Index Tracking)
Time Complexity: O(N) | Space Complexity: O(N) auxiliary for stacks
=======================================================================================
Explanation:
- We use two `vector<int>` acting as stacks to store the indices of `(` and `*`.
- Left-to-right: Match `)` with `(` if possible, otherwise burn a `*`.
- End of string cleanup: Pair remaining `(` with `*`. Ensure the index of `(` is 
  strictly less than the index of `*`, meaning the `*` comes after and can act as `)`.
=======================================================================================
*/

class Solution2 {
public:
    bool checkValidString(string s) {
        vii open_st;
        vii star_st;
        
        for (int i = 0; i < sz(s); i++) {
            if (s[i] == '(') {
                open_st.pb(i);
            } else if (s[i] == '*') {
                star_st.pb(i);
            } else {
                // We have a ')'. Try to match it.
                if (!open_st.empty()) {
                    open_st.ppb();
                } else if (!star_st.empty()) {
                    star_st.ppb();
                } else {
                    // No '(' or '*' available to match the ')'
                    return false;
                }
            }
        }
        
        // Match remaining open brackets with available stars
        while (!open_st.empty() && !star_st.empty()) {
            
            // If the open bracket appears AFTER the star, the star cannot close it
            if (open_st.back() > star_st.back()) {
                return false;
            }
            
            open_st.ppb();
            star_st.ppb();
        }
        
        // If there are leftover open brackets, it's invalid
        return open_st.empty();
    }
};





/*
=======================================================================================
SOLUTION 3: O(1) Space Min-Max Range Tracker
Time Complexity: O(N) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- `cmin` tracks the minimum possible open left brackets.
- `cmax` tracks the maximum possible open left brackets.
- We update the range dynamically. 
- The beauty of resetting `cmin = 0` when it drops below zero is that it corrects 
  the assumption that a `*` acted as a `)`. It effectively says "nevermind, that `*` 
  was actually an empty string".
=======================================================================================
*/

class Solution3 {
public:
    bool checkValidString(string s) {
        int cmin = 0;
        int cmax = 0;
        
        for (char c : s) {
            if (c == '(') {
                cmin++;
                cmax++;
            } else if (c == ')') {
                cmin--;
                cmax--;
            } else {
                // c == '*'
                cmin--; // Assume '*' is ')'
                cmax++; // Assume '*' is '('
            }
            
            // If the maximum possible open count is negative, we have too many ')'
            if (cmax < 0) {
                return false;
            }
            
            // Minimum open count can't be negative. 
            // This just means we shouldn't have treated previous '*' as ')'
            if (cmin < 0) {
                cmin = 0;
            }
        }
        
        // It's valid if it's possible to have exactly 0 open brackets left
        return cmin == 0;
    }
};