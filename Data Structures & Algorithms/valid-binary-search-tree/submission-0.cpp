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
APPROACH 1: Three-Pass Bottom-Up (Subtree Min/Max Tracking)
Time Complexity: O(N) | Space Complexity: O(N) for maps and stack
=======================================================================================
Explanation:
As you suggested, we precompute the absolute minimum and absolute maximum for every 
single subtree using maps (which act as our arrays for tree nodes). 
Then, a final validation pass ensures every node `u` satisfies:
  max_of_left_subtree < u->val < min_of_right_subtree
We cast to `ll` because LeetCode tests include INT_MAX and INT_MIN edge cases!
=======================================================================================
*/

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // Maps to act as our min/max arrays
        unordered_map<TreeNode*, ll> mx_map;
        unordered_map<TreeNode*, ll> mn_map;
        
        // Pass 1: Compute maximums
        auto dfs_max = [&](TreeNode* u, auto&& dfs_max) -> ll {
            if (u == NULL) return -2e18; // Return deeply negative infinity
            
            ll left_mx = dfs_max(u->left, dfs_max);
            ll right_mx = dfs_max(u->right, dfs_max);
            
            mx_map[u] = max({(ll)u->val, left_mx, right_mx});
            return mx_map[u];
        };
        
        // Pass 2: Compute minimums
        auto dfs_min = [&](TreeNode* u, auto&& dfs_min) -> ll {
            if (u == NULL) return 2e18; // Return massively positive infinity
            
            ll left_mn = dfs_min(u->left, dfs_min);
            ll right_mn = dfs_min(u->right, dfs_min);
            
            mn_map[u] = min({(ll)u->val, left_mn, right_mn});
            return mn_map[u];
        };
        
        // Pass 3: Validate against the maps
        auto dfs_check = [&](TreeNode* u, auto&& dfs_check) -> bool {
            if (u == NULL) return true;
            
            // Check left side condition
            if (u->left != NULL && mx_map[u->left] >= u->val) {
                return false;
            }
            // Check right side condition
            if (u->right != NULL && mn_map[u->right] <= u->val) {
                return false;
            }
            
            // Recursively check children
            return dfs_check(u->left, dfs_check) && dfs_check(u->right, dfs_check);
        };
        
        dfs_max(root, dfs_max);
        dfs_min(root, dfs_min);
        
        return dfs_check(root, dfs_check);
    }
};

/*
=======================================================================================
APPROACH 2: One-Pass Top-Down (Range Limiting)
Time Complexity: O(N) | Space Complexity: O(H) for stack
=======================================================================================
Explanation:
Instead of building maps from the bottom up, we carry allowed `min_limit` and 
`max_limit` boundaries from the top down. 
When we go left, the current node becomes the absolute ceiling (`max_limit`).
When we go right, the current node becomes the absolute floor (`min_limit`).
=======================================================================================
*/

class Solution2 {
public:
    bool isValidBST(TreeNode* root) {
        
        auto dfs = [&](TreeNode* u, ll min_limit, ll max_limit, auto&& dfs) -> bool {
            // Base Case: Falling off a leaf is completely valid
            if (u == NULL) return true;
            
            // If the current node violates its allowed boundaries, fail instantly!
            if (u->val <= min_limit || u->val >= max_limit) {
                return false;
            }
            
            // Trust Fall: Check left (update ceiling) AND check right (update floor)
            return dfs(u->left, min_limit, u->val, dfs) && 
                   dfs(u->right, u->val, max_limit, dfs);
        };
        
        // Kick off with infinite boundaries.
        // We use +/- 2e18 because it safely wraps a full 32-bit integer limits.
        return dfs(root, -2e18, 2e18, dfs);
    }
};