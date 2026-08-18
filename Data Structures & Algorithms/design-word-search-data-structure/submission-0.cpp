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
PATTERN: Trie + DFS (Wildcard Search)
Time Complexity: 
  - addWord: O(L) where L is word length
  - search: O(26^M) in the absolute worst-case of all dots, but much faster in practice 
    (O(L) if no dots are present).
Space Complexity: O(Total characters in all words)
=======================================================================================
Explanation:
- `TrieNode` is exactly your standard template.
- `addWord` simply traverses and creates nodes exactly like a normal Trie.
- `search` uses DFS. If the character is '.', we iterate 'j' from 0 to 25 and recursively 
  trust-fall into every non-NULL child.
=======================================================================================
*/

class TrieNode {
public:
    bool isSpecial;
    TrieNode* children[26];
    
    TrieNode() {
        isSpecial = false;
        for(int i = 0; i < 26; i++){
            children[i] = NULL;
        }
    }
};

class WordDictionary {
public:
    TrieNode* root;
    
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* curr = root;
        for(char ch : word) {
            int idx = ch - 'a';
            if(curr->children[idx] == NULL) {
                curr->children[idx] = new TrieNode();
            }
            curr = curr->children[idx]; // Notice we don't need the else, just move down
        }
        curr->isSpecial = true;
    }
    
    bool search(string word) {
        
        // Recursive DFS to handle wildcards
        auto dfs = [&](int i, TrieNode* u, auto&& dfs) -> bool {
            
            // Base Case 1: We reached the end of the word string. 
            // Is the node we are currently standing on marked as the end of a word?
            if (i == word.size()) {
                return u->isSpecial;
            }
            
            char ch = word[i];
            
            // Case A: Wildcard Dot '.'
            if (ch == '.') {
                // Try every single possible path down the Trie
                for (int j = 0; j < 26; j++) {
                    if (u->children[j] != NULL) {
                        // If any of the branches return true, bubble it up!
                        if (dfs(i + 1, u->children[j], dfs)) {
                            return true;
                        }
                    }
                }
                // If we checked all 26 children and none worked out
                return false;
            } 
            // Case B: Standard Character
            else {
                int idx = ch - 'a';
                
                // If the specific child doesn't exist, this path is a dead end
                if (u->children[idx] == NULL) {
                    return false;
                }
                
                // Otherwise, move to the specific child and check the next character
                return dfs(i + 1, u->children[idx], dfs);
            }
        };
        
        // Launch the DFS from the root, looking at the 0-th character of the word
        return dfs(0, root, dfs);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */