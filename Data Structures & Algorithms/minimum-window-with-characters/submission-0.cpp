// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<unordered_map>

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
PATTERN: Variable-Size Sliding Window (Minimum Window)
Time Complexity: O(N + M) | Space Complexity: O(52) -> O(1)
=======================================================================================
Problem: LeetCode 76 - Minimum Window Substring

Intuition:
- Build a target frequency map for `t`. `required` is the number of unique keys.
- Expand `j` and populate our `window` map. If a character meets the target, `formed++`.
- When `formed == required`, the window is valid. 
- While valid, evaluate the minimum size, then shrink `i` to squeeze out extra/useless 
  characters until the window breaks (`formed--`).
=======================================================================================
*/

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";

        unordered_map<char, int> map_t;
        for (char c : t) {
            map_t[c]++;
        }

        int required = map_t.size();
        int formed = 0;
        
        unordered_map<char, int> window;

        int i = 0, j = 0;
        int min_len = INF;
        int start_idx = 0;

        while (j < s.size()) {
            
            // 1. Insert
            char c = s[j];
            window[c]++;

            // If the character is part of `t` and we just reached the exact required amount
            if (map_t.find(c) != map_t.end() && window[c] == map_t[c]) {
                formed++;
            }

            // 2. Shrink and Evaluate (While the window is VALID)
            while (i <= j && formed == required) {
                
                // Evaluate: We only care about minimums now!
                if (j - i + 1 < min_len) {
                    min_len = j - i + 1;
                    start_idx = i;
                }

                // Shrink: Remove the left character
                char left_c = s[i];
                window[left_c]--;
                
                // If we just lost a crucial character, the window breaks!
                if (map_t.find(left_c) != map_t.end() && window[left_c] < map_t[left_c]) {
                    formed--;
                }
                
                i++;
            }

            // 3. Advance
            j++;
        }

        return min_len == INF ? "" : s.substr(start_idx, min_len);
    }
};