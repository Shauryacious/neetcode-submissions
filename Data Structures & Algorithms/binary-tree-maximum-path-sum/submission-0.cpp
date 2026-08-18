/*
=======================================================================================
TREE DP PARADIGM: "The Split vs Extend Machine" (Path Problems)
=======================================================================================
Concept:
At any node 'u', a path passing through it has exactly two geometric options:
1. EXTEND: It acts as a straight line, passing through 'u' from a child up to the parent.
2. SPLIT (Peak): It uses 'u' as the peak of the arch, connecting the left and right children.

The States:
- dp[u] (The Extend State): The max straight-line path starting at 'u' and going down.
  Math: dp[u] = u->val + max(0, max(dp[u->left], dp[u->right]))
  
- maxSum (The Split State): Evaluated globally at every node.
  Math: current_split = u->val + max(0, dp[u->left]) + max(0, dp[u->right])
  
The Negative Weight Rule:
Because we can stop a path anywhere, if a subtree yields a negative sum, we IGNORE IT 
by flooring its value at 0. (i.e., max(0, child_sum)).
=======================================================================================

=======================================================================================
TREE DP PARADIGM: "The Split vs Extend Machine" (Path & Diameter Problems)
=======================================================================================
Concept:
If you pull any valid path in a tree tight, it looks like an inverted "V" (an arch). 
Because a path cannot fork in three directions, every single node 'u' must evaluate 
exactly two geometric possibilities:

1. THE EXTEND STATE (Reporting to Parent):
   'u' acts as a straight line. It can only offer its parent ONE of its legs.
   - Binary Tree Math: dp[u] = u->val + max(dp[u->left], dp[u->right])
   - N-ary Tree Math:  dp[u] = u->val + longest_child_leg

2. THE SPLIT STATE (Testing the Peak):
   What if 'u' is the absolute highest peak of the path? We connect its best legs together 
   and compare it against a global maximum.
   - Binary Tree Math: global_max = max(global_max, u->val + dp[u->left] + dp[u->right])
   - N-ary Tree Math:  global_max = max(global_max, u->val + top1_leg + top2_leg)

Crucial Rules to Remember:
- The Negative Weight Rule: If nodes/edges have negative values, and a path can start/end 
  anywhere, you can just severe the path! Floor child returns at 0: max(0, child_leg).
- Conditional Paths: If a problem has rules (e.g., "nodes must have same value"), a child 
  leg instantly becomes 0 if the condition is broken.

Similar Classic Problems to Practice:
1. Pure Geometry: Diameter of Binary Tree (LeetCode 543)
   https://leetcode.com/problems/diameter-of-binary-tree/

2. N-ary Tree (Top-2 Legs trick): CSES Tree Diameter
   https://cses.fi/problemset/task/1131

3. Conditional Binary Tree: Longest Univalue Path (LeetCode 687)
   https://leetcode.com/problems/longest-univalue-path/

4. The Boss Fight (N-ary + Conditional): Longest Path With Different Adj Chars (LeetCode 2246)
   https://leetcode.com/problems/longest-path-with-different-adjacent-characters/

5. Prefix Sums on Trees: Path Sum III (LeetCode 437)
   https://leetcode.com/problems/path-sum-iii/
=======================================================================================
*/

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        
        // dp[u] = Maximum straight-line path extending downwards from 'u'
        unordered_map<TreeNode*, int> dp;
        
        // The NULL Trick: A non-existent node provides 0 sum.
        // This makes all u->left and u->right lookups 100% safe.
        dp[NULL] = 0;
        
        // Global variable to track the best "Split / Peak" path we ever find
        int maxSum = INT_MIN;
        
        // STATE DEFINITION:
        // Computes dp[u] and evaluates the Split state for the subtree rooted at 'u'
        auto dfs = [&](TreeNode* u, auto&& dfs) -> void {
            if (!u) return;
            
            // Post-order: Get answers from children first
            dfs(u->left, dfs);
            dfs(u->right, dfs);
            
            // Apply the Negative Weight Rule: Floor children's best paths at 0
            // If they are negative, we simply choose not to extend the path into them.
            int left_best  = max(0, dp[u->left]);
            int right_best = max(0, dp[u->right]);
            
            // Evaluate State 1: The Split (Is 'u' the Peak?)
            // Connect Left + 'u' + Right. Update global answer.
            maxSum = max(maxSum, u->val + left_best + right_best);
            
            // Evaluate State 0: The Extend (What 'u' offers its parent)
            // 'u' plus its single best leg.
            dp[u] = u->val + max(left_best, right_best);
        };
        
        dfs(root, dfs);
        
        return maxSum;
    }
};