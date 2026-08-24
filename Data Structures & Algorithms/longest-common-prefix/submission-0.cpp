// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

#define all(x) (x).begin(), (x).end()

/*
=======================================================================================
APPROACH 1: Vertical Scanning
Time Complexity: O(N * M) | Space Complexity: O(1)
Where N is the number of strings, and M is the length of the shortest string.
=======================================================================================
Explanation:
- We use `strs[0]` as our baseline reference.
- The outer loop `i` iterates through the characters of `strs[0]`.
- The inner loop `j` scans downward through the rest of the strings in the array.
- We check two failure conditions:
  1. `i == strs[j].size()`: We reached the end of a shorter string.
  2. `strs[j][i] != c`: We found a character mismatch.
- If either condition is met, we instantly return the valid prefix collected so far 
  using `substr(0, i)`.
=======================================================================================
*/

class Solution1 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        
        // Loop through the characters of the very first string
        for (int i = 0; i < strs[0].size(); i++) {
            char c = strs[0][i]; // The character we expect every other string to have
            
            // Vertically scan the rest of the strings at index 'i'
            for (int j = 1; j < strs.size(); j++) {
                
                // If we hit the end of a shorter string OR find a mismatch
                if (i == strs[j].size() || strs[j][i] != c) {
                    
                    // Return the valid prefix from index 0 up to 'i' characters
                    return strs[0].substr(0, i); 
                }
            }
        }
        
        // If we successfully checked every column and never mismatched, 
        // the entire first string is the common prefix!
        return strs[0];
    }
};

/*
=======================================================================================
APPROACH 2: Lexicographical Sorting
Time Complexity: O(N log N * M) | Space Complexity: O(1) auxiliary
Where N is the number of strings, and M is the maximum length of a string.
=======================================================================================
Explanation:
- We sort the entire array. C++ automatically sorts strings lexicographically (alphabetically).
- Because of this, the first string and the last string will have the LEAST in common.
- Any common prefix shared by the entire array MUST be shared by the first and last string.
- We run a simple loop comparing just those two strings. The moment they differ, we break.
=======================================================================================
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        
        // Step 1: Sort the array lexicographically
        sort(all(strs));
        
        // Step 2: Grab the two extreme strings (most different from each other)
        string first = strs.front();
        string last = strs.back();
        
        string ans = "";
        
        // Step 3: Compare only these two strings
        // We only loop up to the length of the shorter string of the two
        for (int i = 0; i < min(first.size(), last.size()); i++) {
            
            // The instant they mismatch, the common prefix ends
            if (first[i] != last[i]) {
                break;
            }
            
            // Otherwise, append the matching character
            ans += first[i];
        }
        
        return ans;
    }
};