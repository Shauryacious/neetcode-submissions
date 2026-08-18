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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
=======================================================================================
APPROACH 1: Breadth-First Search (Iterative Queue)
Time Complexity: O(N) | Space Complexity: O(W) where W is max width of the tree
=======================================================================================
Explanation:
We push the root into a queue. At the start of each level, we capture `sz = q.size()`. 
This guarantees we only process the exact nodes that belong to the current level, 
while their children get queued up for the next iteration.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vvii ans;
        if(root == NULL) return ans;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()) {
            // Snapshot the number of nodes in the current level
            int sz = q.size();
            vii current_level;
            
            // Process exactly `sz` nodes
            for(int i = 0; i < sz; i++) {
                TreeNode* u = q.front();
                q.pop();
                
                current_level.pb(u->val);
                
                // Queue up the next level's nodes
                if(u->left != NULL) q.push(u->left);
                if(u->right != NULL) q.push(u->right);
            }
            
            ans.pb(current_level);
        }
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 2: Depth-First Search (Recursive Lambda)
Time Complexity: O(N) | Space Complexity: O(H) where H is tree height
=======================================================================================
Explanation:
Using your exact `auto dfs` style, we track the depth `d` as we traverse. 
Because DFS inherently visits the left child before the right, the nodes arrive at 
`ans[d]` in the perfect Left-to-Right order required by the problem!
=======================================================================================
*/

class Solution2 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vvii ans;
        
        auto dfs = [&](TreeNode* u, int d, auto&& dfs) -> void {
            if(u == NULL) return;
            
            // If this is the very first time we've reached this depth, 
            // create a new empty row in our 2D array.
            if(ans.size() == d) {
                ans.pb(vii());
            }
            
            // Append the current node's value to its respective depth's row
            ans[d].pb(u->val);
            
            // Traverse left first, then right (guarantees left-to-right order)
            dfs(u->left, d + 1, dfs);
            dfs(u->right, d + 1, dfs);
        };
        
        // Start DFS at the root with a depth of 0
        dfs(root, 0, dfs);
        
        return ans;
    }
};