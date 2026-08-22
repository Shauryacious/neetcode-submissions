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
PATTERN: Breadth-First Search (Generative Neighbors)
Time Complexity: O(N * L^2) | Space Complexity: O(N * L) for queue and hash set
Where N is the number of words and L is the max length of a word.
=======================================================================================
Explanation:
- We load the dictionary into an `unordered_set` for O(1) lookups.
- We perform a level-by-level BFS sweep (using `sz`), ensuring we find the absolute 
  shortest transformation path.
- For each word, we try mutating every single character from 'a' to 'z'.
- If the mutated word exists in our dictionary, we push it to the queue for the next 
  level and IMMEDIATELY erase it from the dictionary.
- Erasing it acts as our `visited` array, guaranteeing we never process a word twice 
  and naturally shrinking the size of our dictionary.
=======================================================================================
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        
        // Elite Optimization: unordered_set provides O(1) average lookup and deletion
        unordered_set<string> st(wordList.begin(), wordList.end());
        
        if (st.find(endWord) == st.end()) return 0; // The target must exist

        int d = 1; // Transformation length includes the starting word
        queue<string> q;
        q.push(beginWord);

        while (!q.empty()) {
            
            // Your signature wave/level sweep
            int sz = q.size();
            while (sz--) {
                string s = q.front();
                q.pop();
                
                // If we reach the target, return the current depth
                if (s == endWord) {
                    return d;
                }
                
                int n = s.size();

                // Generative Traversal: Try all 26 letters at every index
                for (int i = 0; i < n; i++) {
                    char original_char = s[i]; // Save the original char
                    
                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == original_char) continue; // Skip identical replacements
                        
                        s[i] = c;
                        
                        // If the valid mutation exists in the dictionary
                        if (st.find(s) != st.end()) {
                            q.push(s);
                            st.erase(s); // Mark as visited to prevent cycles
                        }
                    }
                    
                    s[i] = original_char; // Restore the string back to its original state
                }
            }
            d++; // Next wave of mutations will be 1 step deeper
        }
        
        return 0; // Impossible to reach endWord
    }
};