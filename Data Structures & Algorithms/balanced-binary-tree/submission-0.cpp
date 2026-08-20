class Solution {
public:
    bool isBalanced(TreeNode* root) {
        
        // This is our global flag. We assume true until proven otherwise.
        bool is_valid = true;
        
        // The DFS ONLY returns height now.
        auto dfs = [&](TreeNode* node, auto&& dfs) -> int {
            
            // Base case OR if we already found an imbalance elsewhere, stop exploring!
            if (!node || is_valid == false) return 0;
            
            int left_height = dfs(node->left, dfs);
            int right_height = dfs(node->right, dfs);
            
            // If this specific node is unbalanced, immediately trigger the false flag
            if (abs(left_height - right_height) > 1) {
                is_valid = false;
            }
            
            return max(left_height, right_height) + 1;
        };
        
        dfs(root, dfs);
        
        return is_valid;
    }
};