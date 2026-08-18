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
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

/*
=======================================================================================
PATTERN: Divide and Conquer (Tree Construction)
Time Complexity: O(N) | Space Complexity: O(N) for the Hash Map and Stack
=======================================================================================
Explanation:
- We use a global `pre_idx` to sequentially pick nodes from `preorder`. 
- We use an `unordered_map` to find the split point in `inorder` in O(1) time.
- The `dfs` lambda creates the node `u`, recursively attaches its left and right 
  subtrees based on the `inorder` array boundaries, and returns the constructed node.
=======================================================================================
*/

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        
        unordered_map<int, int> in_map;
        int n = inorder.size();
        
        // 1. Map values to their indices in the inorder array for O(1) lookups
        for(int i = 0; i < n; i++) {
            in_map[inorder[i]] = i;
        }
        
        int pre_idx = 0;
        
        // 2. The recursive builder
        auto dfs = [&](int in_start, int in_end, auto&& dfs) -> TreeNode* {
            
            // Base case: If boundaries cross, there are no nodes left for this subtree
            if (in_start > in_end) {
                return NULL;
            }
            
            // The current root is the next available element in preorder
            int root_val = preorder[pre_idx++];
            TreeNode* u = new TreeNode(root_val);
            
            // Find where this root is located in the inorder array
            int mid = in_map[root_val];
            
            // Trust Fall: Build the left and right subtrees
            // Left subtree gets elements strictly before `mid`
            u->left = dfs(in_start, mid - 1, dfs);
            
            // Right subtree gets elements strictly after `mid`
            u->right = dfs(mid + 1, in_end, dfs);
            
            return u;
        };
        
        // Kick off the recursion with the full boundaries of the inorder array
        return dfs(0, n - 1, dfs);
    }
};