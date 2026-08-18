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
APPROACH 1: Simultaneous DFS (Recursive Lambda)
Time Complexity: O(min(N, M)) | Space Complexity: O(min(H1, H2))
=======================================================================================
Explanation:
We pass both nodes `u` and `v` into our DFS simultaneously. 
By chaining the recursive calls with `&&`, C++ performs short-circuit evaluation. 
If the left subtrees don't match, it instantly returns false without ever wasting 
time exploring the right subtrees!
=======================================================================================
*/

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        
        auto dfs = [&](TreeNode* u, TreeNode* v, auto&& dfs) -> bool {
            // Both nodes are NULL -> structural match
            if (u == NULL && v == NULL) return true;
            
            // Only one node is NULL -> structural mismatch
            if (u == NULL || v == NULL) return false;
            
            // Values differ -> value mismatch
            if (u->val != v->val) return false;
            
            // Both children branches must perfectly match
            bool ans = false;

            ans |= (dfs(u->left, v->left, dfs) && dfs(u->right, v->right, dfs));

            return ans;
        };
        
        return dfs(p, q, dfs);
    }
};

/*
=======================================================================================
APPROACH 2: Pure Recursion (The One-Liner CP Way)
Time Complexity: O(min(N, M)) | Space Complexity: O(min(H1, H2))
=======================================================================================
Explanation:
Because the problem's given function signature `isSameTree(TreeNode* p, TreeNode* q)` 
matches our required recursive state perfectly, we don't actually need a helper lambda! 
We can just recursively call the class method directly.
=======================================================================================
*/

class Solution2 {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base cases
        if (!p && !q) return true;
        if (!p || !q) return false;
        if (p->val != q->val) return false;
        
        // Trust fall on the subtrees
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};