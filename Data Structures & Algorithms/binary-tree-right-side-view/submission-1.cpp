// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<stack>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<chrono>
#include<random>
#include<string>
#include<functional>
#include<iomanip>
#include<limits>
#include<array>
#include<utility>
#include<iterator>
#include<cstring>

using namespace std;

// Define Constants & Macros
#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e9 
#define nl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define py cout<<"YES"<<nl
#define pn cout<<"NO"<<nl
#define pm cout<<"-1"<<nl
#define all(x) (x).begin(), (x).end()

// Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<pll> vpll;

#define vvpll vector<vpll>

/*
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
*/

/*
=======================================================================================
SOLUTION 1: Breadth-First Search (Level-Order Sweep)
Time Complexity: O(N) | Space Complexity: O(W) where W is the max width of the tree
=======================================================================================
Explanation:
- We use a queue to process the tree exactly one horizontal level at a time.
- `sz(q)` takes a snapshot of the exact number of nodes on the current level.
- We iterate through that level from left to right.
- When `i == sz - 1`, we are holding the absolute last (rightmost) node of that level. 
  We record it and move on to the next depth.
=======================================================================================
*/

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        
        queue<TreeNode*> q;
        vii ans;
        
        q.push(root);
        
        while (!q.empty()) {
            int current_level_size = sz(q);
            
            for (int i = 0; i < current_level_size; i++) {
                TreeNode* u = q.front();
                q.pop();
                
                // If this is the absolute last node in the current level's queue
                if (i == current_level_size - 1) {
                    ans.pb(u->val);
                }
                
                // Push children for the next level
                if (u->left) q.push(u->left);
                if (u->right) q.push(u->right);
            }
        }

        return ans;
    }
};



/*
=======================================================================================
APPROACH 2: Depth-First Search (Right-to-Left Pre-Order)
Time Complexity: O(N) | Space Complexity: O(H) auxiliary (H = height of tree)
=======================================================================================
Explanation:
- We traverse the tree, but we deliberately visit the RIGHT child before the LEFT child.
- We keep track of our current `depth` (starting at 0).
- Because we prioritize the right side, the FIRST time we reach a brand new depth, 
  that node is mathematically guaranteed to be the rightmost node at that level.
- We know we've reached a new depth when `depth == ans.size()`.
=======================================================================================
*/

class Solution2 {
public:
    vector<int> rightSideView(TreeNode* root) {
        vii ans;
        
        // STATE DEFINITION: node pointer and current depth
        auto dfs = [&](TreeNode* node, int depth, auto&& dfs) -> void {
            if (!node) return;
            
            // If the size of our answer array matches the current depth, 
            // it means we are visiting this depth for the very first time!
            if (depth == sz(ans)) {
                ans.pb(node->val);
            }
            
            // Explore RIGHT first, then LEFT
            dfs(node->right, depth + 1, dfs);
            dfs(node->left, depth + 1, dfs);
        };
        
        dfs(root, 0, dfs);
        
        return ans;
    }
};