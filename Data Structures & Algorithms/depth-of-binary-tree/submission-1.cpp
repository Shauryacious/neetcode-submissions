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
APPROACH 1: Top-Down DFS (Your Style)
Time Complexity: O(N) | Space Complexity: O(H) where H is tree height
=======================================================================================
Explanation:
We pass the current depth `d` down the recursive tree. At every valid node, we update 
the global maximum height `h`. By checking `if(u->left != NULL)` before calling, 
we prevent unnecessary calls to NULL nodes, optimizing our stack space!
=======================================================================================
*/

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        
        int h = 0;
        
        auto dfs = [&](TreeNode* u, int d, auto && dfs) -> void {
            h = max(h, d);
            
            if (u->left != NULL) {
                dfs(u->left, d + 1, dfs);
            }
            if (u->right != NULL) {
                dfs(u->right, d + 1, dfs);
            }
        };
        
        dfs(root, 1, dfs);
        
        return h;
    }
};

/*
=======================================================================================
APPROACH 2: Bottom-Up DP (The CP One-Liner)
Time Complexity: O(N) | Space Complexity: O(H)
=======================================================================================
Explanation:
Instead of passing the depth down, we can ask the children to pass their depths UP.
The maximum depth of any tree is simply 1 (for the current node) plus the maximum 
depth of its left and right subtrees. 
This allows us to completely drop the `h` variable and the `dfs` lambda entirely!
=======================================================================================
*/

class Solution2 {
public:
    int maxDepth(TreeNode* root) {
        // Base Case: If we step off a leaf, the depth is 0
        if (root == NULL) {
            return 0;
        }
        
        // Trust Fall: Return 1 for myself, plus the max of my subtrees
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};