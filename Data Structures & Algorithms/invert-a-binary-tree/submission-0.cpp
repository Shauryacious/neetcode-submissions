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
PATTERN: Tree Traversal (Recursive Lambda)
Time Complexity: O(N) | Space Complexity: O(H) where H is the height of the tree
=======================================================================================
Problem: LeetCode 226 - Invert Binary Tree

Intuition:
- To invert a binary tree, we just need to swap the left and right pointers of every 
  single node.
- We use a pre-order traversal: 
  1. Swap the children of the current node.
  2. Recursively call the lambda on the left child.
  3. Recursively call the lambda on the right child.
=======================================================================================
*/

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

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        
        // The recursive lambda function
        auto f = [&](TreeNode* node, auto&& f) -> void {
            
            // Base Case: If we hit a NULL node (falling off a leaf), just stop.
            if (node == NULL) {
                return;
            }
            
            // 1. Swap the left and right children
            swap(node->left, node->right);
            
            // 2. Trust Fall: Recursively invert the subtrees
            f(node->left, f);
            f(node->right, f);
        };
        
        // Kick off the recursion from the root
        f(root, f);
        
        return root;
    }
};