// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<unordered_map>

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
APPROACH 1: Recursive BST Traversal (Your Recursive DFS Style)
Time Complexity: O(H) | Space Complexity: O(H)
=======================================================================================
Explanation:
We strictly use the `auto dfs = [&](TreeNode* u, ...)` lambda. Because it is a 
Binary Search Tree, the math inherently tells us where to go.
- If both nodes are smaller than `u`, the LCA is in the left subtree.
- If both are greater, the LCA is in the right subtree.
- If they split (one is smaller, one is greater, or one is exactly `u`), `u` is the LCA!
=======================================================================================
*/

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ans = NULL;
        
        auto dfs = [&](TreeNode* u, auto&& dfs) -> void {
            if(u == NULL) return;
            
            // Both targets are in the left branch
            if(p->val < u->val && q->val < u->val) {
                dfs(u->left, dfs);
            }
            // Both targets are in the right branch
            else if(p->val > u->val && q->val > u->val) {
                dfs(u->right, dfs);
            }
            // The paths diverge right here. We found the LCA!
            else {
                ans = u;
                return;
            }
        };
        
        dfs(root, dfs);
        
        return ans;
    }
};

/*
=======================================================================================
APPROACH 2: Binary Lifting (The Ultimate CP Graph Algorithm)
Time Complexity: O(N log N) Precomputation | O(log N) Query
Space Complexity: O(N log N)
=======================================================================================
Explanation:
We apply your exact K-th Ancestor Binary Lifting template to TreeNodes. 
1. `dfs` runs down the tree to assign depths and fill the 0-th column of the `anc` map.
2. We precompute the table using the `mid_anc` jump logic.
3. To find the LCA:
   - Identify the deeper node and jump it up using the bitwise check until `depth[u] == depth[v]`.
   - If they aren't the same node yet, jump both `u` and `v` up simultaneously from 
     the largest power of 2 down to 0, ONLY if `anc[u][i] != anc[v][i]`. 
   - This leaves them exactly one step below the LCA. Returning `anc[u][0]` gives the answer!
=======================================================================================
*/

class Solution2 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int LOG = 20; // log2(10^5) is ~17, so 20 is completely safe
        
        unordered_map<TreeNode*, vector<TreeNode*>> anc;
        unordered_map<TreeNode*, int> depth;
        vector<TreeNode*> nodes; // Array to easily iterate through all seen nodes
        
        // 1. DFS to initialize depths and immediate parents
        auto dfs = [&](TreeNode* u, TreeNode* parent, int d, auto&& dfs) -> void {
            if(u == NULL) return;
            
            nodes.pb(u);
            depth[u] = d;
            
            // Initialize the ancestor row for node `u`
            anc[u] = vector<TreeNode*>(LOG, NULL);
            anc[u][0] = parent; // 0-th ancestor is the direct parent
            
            dfs(u->left, u, d + 1, dfs);
            dfs(u->right, u, d + 1, dfs);
        };
        
        dfs(root, NULL, 0, dfs);
        
        // 2. Precompute the ancestor table using the `mid_anc` style
        for(int k = 1; k < LOG; k++){
            for(TreeNode* u : nodes){
                TreeNode* mid_anc = anc[u][k - 1];
                
                if(mid_anc != NULL){
                    anc[u][k] = anc[mid_anc][k - 1];
                }
            }
        }
        
        // 3. LCA Query Algorithm
        TreeNode* u = p;
        TreeNode* v = q;
        
        // Step A: Ensure `u` is always the deeper node
        if(depth[u] < depth[v]){
            swap(u, v);
        }
        
        // Step B: Equalize depths by jumping `u` upwards
        int diff = depth[u] - depth[v];
        for(int i = 0; i < LOG; i++){
            if((diff >> i) & 1){
                u = anc[u][i];
            }
        }
        
        // If they collided while equalizing, `v` was already an ancestor of `u`
        if(u == v){
            return u;
        }
        
        // Step C: Jump them both simultaneously
        // We go from largest jump down to smallest jump
        for(int i = LOG - 1; i >= 0; i--){
            
            // If they land on DIFFERENT nodes, we haven't overshot the LCA. Jump!
            if(anc[u][i] != anc[v][i]){
                u = anc[u][i];
                v = anc[v][i];
            }
        }
        
        // u and v are now standing exactly one level below the LCA
        TreeNode* ans = anc[u][0];
        
        return ans;
    }
};