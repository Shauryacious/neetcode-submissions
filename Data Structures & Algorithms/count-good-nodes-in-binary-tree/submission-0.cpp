/*
=======================================================================================
SOLUTION 1: Void Return + External Counter
Time Complexity: O(N) | Space Complexity: O(H) auxiliary
=======================================================================================
Explanation:
- We declare `ans = 0` outside the DFS.
- The DFS returns `void`. Its only job is to walk the tree and pass the state 
  (`max_so_far`) downward.
- Whenever it finds a good node, it directly modifies the external `ans` variable.
=======================================================================================
*/

class Solution { 
public:
    int goodNodes(TreeNode* root) {
        if (!root) return 0;
        
        int ans = 0; // Our external tracker
        
        auto dfs = [&](TreeNode* node, int max_so_far, auto&& dfs) -> void {
            if (!node) return;
            
            // If it clears the hurdle, increment our tracker and update the hurdle
            if (node->val >= max_so_far) {
                ans++;
                max_so_far = node->val;
            }
            
            // Continue the traversal
            dfs(node->left, max_so_far, dfs);
            dfs(node->right, max_so_far, dfs);
        };
        
        dfs(root, root->val, dfs);
        
        return ans;
    }
};