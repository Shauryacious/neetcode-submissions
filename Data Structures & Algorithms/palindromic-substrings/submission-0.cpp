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
PATTERN: Expand Around Center (Counting Variation)
Time Complexity: O(N^2) | Space Complexity: O(1)
=======================================================================================
Explanation:
- We iterate through every index `i`.
- `expand(i, i)` counts all odd-length palindromes centered at `i`.
- `expand(i, i + 1)` counts all even-length palindromes centered between `i` and `i+1`.
- Every successful match inside the `while` loop directly translates to one valid 
  palindromic substring. We just sum them all up!
=======================================================================================
*/

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        int ans = 0;

        // HELPER LAMBDA: 
        // Expands outward and returns the NUMBER of valid palindromes found from this center.
        auto expand = [&](int l, int r) -> int {
            int count = 0;
            
            while(l >= 0 && r < n && s[l] == s[r]) {
                count++; // We found a valid palindromic substring!
                l--;
                r++;
            }
            
            return count;
        };

        for(int i = 0; i < n; i++) {
            // UNIVERSE 1: Odd length palindromes (Center is a single character)
            ans += expand(i, i);
            
            // UNIVERSE 2: Even length palindromes (Center is exactly between two characters)
            ans += expand(i, i + 1);
        }

        return ans;
    }
};