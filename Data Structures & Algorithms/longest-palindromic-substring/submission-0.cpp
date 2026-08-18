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
PATTERN: Expand Around Center (Two Pointers)
Time Complexity: O(N^2) | Space Complexity: O(1)
=======================================================================================
Explanation:
- We iterate through every index `i` in the string.
- We try to build the longest odd-length palindrome centered exactly at `i`.
- We try to build the longest even-length palindrome centered between `i` and `i+1`.
- We use a helper lambda `expand` to push the left and right pointers outward.
- We track the absolute maximum length found and its starting index to slice the 
  final substring.
=======================================================================================
*/

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        if(n == 0) return "";
        
        int best_start = 0;
        int max_len = 1;

        // HELPER LAMBDA: 
        // Takes a left and right center, and expands outward while characters match.
        // Returns the length of the valid palindrome found.
        auto expand = [&](int l, int r) -> int {
            while(l >= 0 && r < n && s[l] == s[r]) {
                l--;
                r++;
            }
            
            // When the loop breaks, l and r have moved ONE step too far.
            // The valid palindrome is strictly from (l + 1) to (r - 1).
            // Length = (r - 1) - (l + 1) + 1 = r - l - 1
            return r - l - 1;
        };

        for(int i = 0; i < n; i++) {
            
            // UNIVERSE 1: Assume the palindrome is ODD length (Center is s[i])
            int len1 = expand(i, i);
            
            // UNIVERSE 2: Assume the palindrome is EVEN length (Center is between s[i] and s[i+1])
            int len2 = expand(i, i + 1);
            
            // Get the best palindrome from this specific center
            int current_max = max(len1, len2);
            
            // If it beats our global record, lock in the new start index and length
            if(current_max > max_len) {
                max_len = current_max;
                
                // MATH TRICK: 
                // Whether it was even or odd length, if we are centered at 'i',
                // the start of the palindrome is always i - (len - 1) / 2.
                best_start = i - (max_len - 1) / 2;
            }
        }

        // Return the winning substring
        return s.substr(best_start, max_len);
    }
};