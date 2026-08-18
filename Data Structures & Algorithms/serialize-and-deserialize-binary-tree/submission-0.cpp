// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<queue>

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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
=======================================================================================
PATTERN: Tree Serialization (Pre-order State Machine)
Time Complexity: O(N) | Space Complexity: O(N) for string/queue/stack
=======================================================================================
Explanation:
- `serialize`: Traverses Pre-order, adding node values followed by a comma. NULL 
  nodes are recorded as `#,`.
- `deserialize`: Splits the string by commas into a queue. A recursive DFS consumes 
  the queue one element at a time. If it sees `#`, it terminates the branch. 
  Otherwise, it builds the node and recursively builds the left and right subtrees!
=======================================================================================
*/

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s = "";
        
        auto dfs = [&](TreeNode* u, auto&& dfs) -> void {
            if (u == NULL) {
                s += "#,";
                return;
            }
            
            // Pre-order: Node -> Left -> Right
            s += to_string(u->val) + ",";
            dfs(u->left, dfs);
            dfs(u->right, dfs);
        };
        
        dfs(root, dfs);
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        queue<string> q;
        string current_val = "";
        
        // 1. Parse the string and dump all tokens into a queue
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ',') {
                q.push(current_val);
                current_val = ""; // Reset for the next number
            } else {
                current_val += data[i];
            }
        }
        
        // 2. The Builder DFS
        auto dfs = [&](auto&& dfs) -> TreeNode* {
            // Failsafe (should theoretically never trigger on valid input)
            if (q.empty()) return NULL;
            
            // Consume the front of the queue
            string val = q.front();
            q.pop();
            
            // If it's the Null Marker, terminate this branch
            if (val == "#") {
                return NULL;
            }
            
            // Build the current node
            TreeNode* u = new TreeNode(stoi(val));
            
            // Trust Fall: Build the subtrees using the rest of the queue
            u->left = dfs(dfs);
            u->right = dfs(dfs);
            
            return u;
        };
        
        return dfs(dfs);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));