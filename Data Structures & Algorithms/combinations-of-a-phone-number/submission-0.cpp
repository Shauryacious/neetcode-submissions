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
PATTERN: Multi-Branch Backtracking
Time Complexity: O(4^N * N) where N is length of digits | Space: O(N) auxiliary stack
=======================================================================================
Explanation:
- We use a global/local array `pad` to instantly map digits to letters.
- At index `i` of the input string, we find the letters available for that digit.
- We loop through every available letter.
- Action: Push the letter into our `curr` string bucket.
- Recurse: Move to index `i + 1` to process the next digit in the input.
- Backtrack: Pop the letter out of the bucket to make room for the next letter 
  in the `for` loop.
=======================================================================================
*/

class Solution {
public:
    vs letterCombinations(string digits) {
        int n = digits.size();
        vs ans;
        
        // Edge Case: If the input is empty, return an empty array immediately.
        // Otherwise, our logic would return [""] which is incorrect.
        if (n == 0) return ans;
        
        // The mapping array. Indices 0 and 1 are intentionally left blank.
        vs pad = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        
        auto f = [&](int i, string& curr, auto && f) -> void {
            
            // Base Case: Our string has a letter for every digit in the input
            if (i == n) {
                ans.pb(curr);
                return;
            }
            
            // Convert the character digit (e.g., '2') to an integer index (2)
            int digit = digits[i] - '0';
            string letters = pad[digit];
            
            // Try every possible letter on this specific phone button
            for (char c : letters) {
                
                curr.pb(c);             // Take
                f(i + 1, curr, f);      // Recurse to the next digit
                curr.pop_back();        // Backtrack
            }
        };
        
        string curr = "";
        f(0, curr, f);
        
        return ans;
    }
};