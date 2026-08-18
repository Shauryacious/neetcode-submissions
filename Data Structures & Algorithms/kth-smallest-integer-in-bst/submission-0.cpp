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
APPROACH 1: In-Order Traversal with Early Stopping
Time Complexity: O(H + K) | Space Complexity: O(H) for recursion stack
=======================================================================================
Explanation:
We capture `k` by reference (or just let the lambda capture the class-level `k`). 
As we process nodes in ascending order, we decrement `k`. 
When `k == 0`, we lock in our answer and use it as a flag (`ans != -1`) to prevent 
any further recursive calls, massively speeding up the traversal.
=======================================================================================
*/

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        int ans = -1;
        
        auto dfs = [&](TreeNode* u, auto&& dfs) -> void {
            // Base case or if we already found the answer, stop exploring
            if (u == NULL || ans != -1) return;
            
            // 1. Go as far Left as possible (find the absolute smallest first)
            dfs(u->left, dfs);
            
            // 2. Process the current node
            k--;
            if (k == 0) {
                ans = u->val;
                return; 
            }
            
            // 3. Go Right (only if we haven't found the answer yet)
            dfs(u->right, dfs);
        };
        
        dfs(root, dfs);
        
        return ans;
    }
};