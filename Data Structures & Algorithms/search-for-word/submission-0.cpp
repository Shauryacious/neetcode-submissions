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
PATTERN: Grid DFS + Backtracking
Time Complexity: O(N * M * 4^L) where L is length of word | Space: O(L) for recursion
=======================================================================================
Explanation:
- We iterate through the grid and fire a DFS only when `board[i][j] == word[0]`.
- Inside `dfs`, we check bounds and character matches. 
- If valid, we mask the character as `#` (acting as our `visited` check).
- We use `dr` and `dc` arrays to elegantly loop through Up, Down, Left, Right.
- Once the 4 directions are explored, we backtrack and unmask the character!
=======================================================================================
*/

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        
        // Direction vectors for cleanly exploring Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        auto dfs = [&](int r, int c, int idx, auto&& dfs) -> bool {
            // Base Case 1: If idx reaches the word length, we matched every character!
            if (idx == word.size()) {
                return true;
            }
            
            // Base Case 2: Out of bounds OR character mismatch OR hitting visited cell ('#')
            if (r < 0 || r >= n || c < 0 || c >= m || board[r][c] != word[idx]) {
                return false;
            }
            
            // 1. Mask the current cell (The "Take" / Visited step)
            char temp = board[r][c];
            board[r][c] = '#';
            
            // 2. Trust Fall into all 4 directions
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // If any branch finds the word, instantly bubble up `true`
                if (dfs(nr, nc, idx + 1, dfs)) {
                    return true;
                }
            }
            
            // 3. THE BACKTRACK: Restore the cell for other DFS paths
            board[r][c] = temp;
            
            return false;
        };
        
        // Launch the probe ONLY from matching first characters
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == word[0]) {
                    
                    // If a probe returns true, the entire grid search is over
                    if (dfs(i, j, 0, dfs)) {
                        return true;
                    }
                    
                }
            }
        }
        
        return false;
    }
};