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
PATTERN: Trie + Grid DFS Backtracking
Time Complexity: O(M * N * 4^L) where L is max word length (Heavily Pruned!)
Space Complexity: O(Total letters in dictionary) for the Trie
=======================================================================================
Explanation:
- We modify the `TrieNode` to store the actual `string word` instead of a boolean.
- We run DFS from every grid cell. If the grid character isn't in the Trie branch, 
  we instantly prune the search (return).
- We use the `#` masking trick for in-place visited checks.
- When we find a word, we append it to `ans` and erase it from the Trie to 
  prevent duplicate entries without needing a `set`.
=======================================================================================
*/

class TrieNode {
public:
    string word; // Storing the actual word instead of boolean 'isSpecial'
    TrieNode* children[26];
    
    TrieNode() {
        word = "";
        for(int i = 0; i < 26; i++){
            children[i] = NULL;
        }
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        
        // 1. Build the Trie
        TrieNode* root = new TrieNode();
        for(string w : words) {
            TrieNode* curr = root;
            for(char ch : w) {
                int idx = ch - 'a';
                if(curr->children[idx] == NULL) {
                    curr->children[idx] = new TrieNode();
                }
                curr = curr->children[idx];
            }
            curr->word = w; // Embed the full word at the terminal node
        }
        
        int n = board.size();
        int m = board[0].size();
        vector<string> ans;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // 2. The Smart DFS
        auto dfs = [&](int r, int c, TrieNode* u, auto&& dfs) -> void {
            char ch = board[r][c];
            
            // Base Case 1: Visited cell
            if (ch == '#') return;
            
            // Base Case 2: The current character is a dead end in our Trie! (Prune)
            int idx = ch - 'a';
            if (u->children[idx] == NULL) return;
            
            // Move down the Trie
            TrieNode* next_node = u->children[idx];
            
            // Base Case 3: We found a word!
            if (next_node->word != "") {
                ans.pb(next_node->word);
                next_node->word = ""; // Erase to prevent duplicate finds
            }
            
            // Mask the cell (Visited)
            board[r][c] = '#';
            
            // Trust Fall into 4 directions
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    dfs(nr, nc, next_node, dfs);
                }
            }
            
            // THE BACKTRACK: Restore the cell
            board[r][c] = ch;
        };
        
        // 3. Launch the probe from every cell
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dfs(i, j, root, dfs);
            }
        }
        
        return ans;
    }
};