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
=============================================================================================
PROBLEM STATEMENT: 
Given an undirected graph (reported as a tree/forest), find the longest simple path 
between any two nodes — i.e., the diameter.

INTERVIEW NOTES & FOLLOW-UPS:
1. Weighted Trees: 
   The Double DFS method (Approach 2) works perfectly for non-negative weighted edges 
   (just pass `dist + weight` instead of `dist + 1`). It FAILS for negative edge weights. 
   The DP/LCA method (Approach 1) can be adapted to handle negative weights.

2. Forests (Disconnected components): 
   Run a loop from 1 to N. If a node is unvisited, run the algorithm (Double DFS or DP) 
   on that connected component, mark its nodes as visited, and update a global 
   `max_forest_diameter`.

3. Cycles (NP-Hard Trap): 
   If the graph has cycles, it is no longer a tree. Finding the longest simple path in a 
   general graph with cycles is NP-Hard (reduces to the Hamiltonian Path problem). 
   Clarify this immediately with the interviewer!

4. Returning the Actual Path (Not just length):
   Use the Double DFS method. During the second DFS, pass a `vector<int>& parent` array 
   to track where each node came from. Once you hit the farthest node V, backtrack using 
   the parent array until you reach U, pushing nodes into a path vector.

5. Alternative Approaches:
   Topological sorting (peeling leaves inward like Minimum Height Trees - LC 310) can 
   find the midpoint of the diameter, but it is overly complicated if you only need the length.
   https://leetcode.com/problems/minimum-height-trees/description/
=============================================================================================
*/


// // Definition for a binary tree node (Used in Approach 1)
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// };


/*
=============================================================================================
APPROACH 1: One-Pass DP (LCA Method for Binary Trees - LC 543)
Time Complexity: O(N)
Space Complexity: O(H) where H is the height of the tree (recursion stack)

Logic: 
Treat each node as the Lowest Common Ancestor (LCA) of the longest path passing through it.
The longest path through a node is the sum of the max depths of its left and right subtrees.
=============================================================================================
// */


class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;

        // STATE DEFINITION:
        // Returns the maximum depth of the subtree rooted at 'node'
        auto f = [&](TreeNode* u, auto&& f) -> int {
            // Base case
            if (!u) return 0;

            int left_depth = 0;
            int right_depth = 0;

            // Explicit branching for children
            if (u->left) {
                left_depth = f(u->left, f);
            }
            if (u->right) {
                right_depth = f(u->right, f);
            }

            // Treat current node as the LCA of the longest path
            diameter = max(diameter, left_depth + right_depth);

            // Return max depth to the parent
            return max(left_depth, right_depth) + 1;
        };

        f(root, f);
        return diameter;
    }
};


// /*
// =============================================================================================
// APPROACH 2: Double DFS (For General N-ary Trees/Graphs - LC 1245)
// Time Complexity: O(N)
// Space Complexity: O(N) for adjacency list and recursion stack

// Logic:
// 1. Start DFS from any random node (e.g., node 0) to find the farthest node 'U'.
// 2. Node 'U' is guaranteed to be one endpoint of the diameter.
// 3. Start a second DFS from node 'U' to find the farthest node 'V'.
// 4. The distance between 'U' and 'V' is the diameter of the tree.
// =============================================================================================
// */

// class Solution {
// public:
//     int treeDiameter(vector<vector<int>>& edges) {
//         // n edges means n + 1 nodes in a valid tree
//         int n = edges.size() + 1;
//         vvii adj(n);
        
//         for(auto& e : edges) {
//             adj[e[0]].pb(e[1]);
//             adj[e[1]].pb(e[0]);
//         }

//         int farthest_node = 0;
//         int max_dist = 0;

//         // STATE DEFINITION:
//         // u -> current node
//         // p -> parent node (to prevent infinite loops going backwards)
//         // dist -> distance from the DFS starting node
//         auto dfs = [&](int u, int p, int dist, auto&& dfs) -> void {
//             // Update global trackers if we found a farther node
//             if (dist > max_dist) {
//                 max_dist = dist;
//                 farthest_node = u;
//             }

//             // Explicit branch: visit all neighbors except the parent
//             for (int v : adj[u]) {
//                 if (v != p) {
//                     dfs(v, u, dist + 1, dfs);
//                 }
//             }
//         };

//         // Pass 1: Start from arbitrary node 0 to find one endpoint of the diameter (U)
//         dfs(0, -1, 0, dfs);

//         // Pass 2: Reset distance and run DFS from the endpoint U to find endpoint V
//         int endpoint_u = farthest_node;
//         max_dist = 0; // Reset for the second pass
        
//         dfs(endpoint_u, -1, 0, dfs);

//         // max_dist is now the length of the diameter (distance from U to V)
//         return max_dist;
//     }
// };


// /*
// =============================================================================================
// APPROACH 2.2: Double BFS (Level-by-Level with Queue)
// Time Complexity: O(N)
// Space Complexity: O(N) for adjacency list, queue, and distance vector

// Logic:
// 1. Start a level-by-level BFS from an arbitrary node (0).
// 2. Populate the `dist` vector. The node with the maximum distance is 'U' (one endpoint of the diameter).
// 3. Start a second level-by-level BFS from 'U'.
// 4. The maximum value in the new `dist` vector is the diameter of the tree.
// =============================================================================================
// */
// class Solution {
// public:
//     int treeDiameter(vector<vector<int>>& edges) {
//         // n edges means n + 1 nodes in a valid tree
//         int n = edges.size() + 1;
//         vvii adj(n);
        
//         for(auto& e : edges) {
//             adj[e[0]].pb(e[1]);
//             adj[e[1]].pb(e[0]);
//         }

//         // BFS DEFINITION:
//         // Level-by-level BFS that returns a fully populated distance vector
//         auto bfs = [&](int start_node) -> vii {
//             vii dist(n, -1);
//             queue<int> q;
            
//             q.push(start_node);
//             dist[start_node] = 0;
            
//             int d = 0; // Tracks the current depth/level
            
//             while(!q.empty()) {
//                 int sz = q.size();
//                 while(sz--) {
//                     int u = q.front();
//                     q.pop();
                    
//                     // Explicit branch: visit all unvisited neighbors
//                     for(int v : adj[u]) {
//                         if(dist[v] == -1) {
//                             dist[v] = d + 1;
//                             q.push(v);
//                         }
//                     }
//                 }
//                 d++; // Increment distance for the next level
//             }
            
//             return dist;
//         };

//         // Pass 1: BFS from arbitrary node 0 to find endpoint U
//         vii dist1 = bfs(0);
        
//         int endpoint_u = 0;
//         int max_dist = -1;
//         for(int i = 0; i < n; i++) {
//             if(dist1[i] > max_dist) {
//                 max_dist = dist1[i];
//                 endpoint_u = i;
//             }
//         }

//         // Pass 2: BFS from endpoint U to find the actual diameter
//         vii dist2 = bfs(endpoint_u);
        
//         int diameter = 0;
//         for(int i = 0; i < n; i++) {
//             if(dist2[i] > diameter) {
//                 diameter = dist2[i];
//             }
//         }

//         return diameter;
//     }
// };


/*
=============================================================================================
APPROACH 3: One-Pass DP / "Split vs Extend" (Using unordered_map DP)
Time Complexity: O(N)
Space Complexity: O(N) for adjacency list, recursion stack, and map

Logic:
This forces your explicit `unordered_map` Tree DP paradigm into an N-ary graph. 
Instead of returning integers, we strictly rely on post-order traversal to populate `dp[v]` 
for all children before evaluating `dp[u]`. 

Because a node can have many children, we can't just check `dp[left]` and `dp[right]`. 
We iterate through the children, reading their pre-computed `dp` values to dynamically 
track the top 2 longest legs.
=============================================================================================
*/

class Solution4 {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        // n edges means n + 1 nodes in a valid tree
        int n = edges.size() + 1;
        vvii adj(n);
        
        for(auto& e : edges) {
            adj[e[0]].pb(e[1]);
            adj[e[1]].pb(e[0]);
        }

        // dp[u] = Maximum straight-line path extending downwards from 'u'
        unordered_map<int, int> dp;
        
        int max_diameter = 0;

        // STATE DEFINITION:
        // Evaluates the Extend state (dp[u]) and Split state (max_diameter) for node 'u'.
        auto dfs = [&](int u, int p, auto&& dfs) -> void {
            
            int top1 = 0; // Longest leg from any child
            int top2 = 0; // Second longest leg from any child
            
            for (int v : adj[u]) {
                if (v == p) continue; // Prevent going back up to parent
                
                // Post-order: Guarantee dp[v] is fully calculated first
                dfs(v, u, dfs);
                
                // The leg extending into child 'v' includes the edge connecting 'u' to 'v'
                int child_leg = dp[v] + 1;
                
                // Dynamically track the top 2 longest legs among all children
                if (child_leg > top1) {
                    top2 = top1;
                    top1 = child_leg;
                } else if (child_leg > top2) {
                    top2 = child_leg;
                }
            }
            
            // THE SPLIT STATE (Testing the Peak)
            // What if 'u' is the highest point of the diameter?
            max_diameter = max(max_diameter, top1 + top2);
            
            // THE EXTEND STATE (Storing for Parent)
            // 'u' saves its single longest extending leg in the DP map
            dp[u] = top1;
        };

        // Start DFS from any arbitrary root (e.g., node 0), with parent -1
        dfs(0, -1, dfs);
        
        return max_diameter;
    }
};