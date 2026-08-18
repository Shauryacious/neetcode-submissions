// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<numeric>

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
APPROACH 1: Void DFS (Cycle Detection & Connectivity)
Time Complexity: O(V + E) | Space Complexity: O(V + E)
=======================================================================================
Explanation:
- Fast Fail: A valid tree MUST have exactly n - 1 edges. 
- We use your signature `void dfs` with an external `bool cycle = false;` flag.
- We pass the `p` (parent) into our DFS so we don't falsely flag the edge we just 
  arrived from as a cycle.
- If we hit an already visited node that isn't `p`, we flip `cycle = true` and return.
- After the DFS, we verify that no cycle was found AND that every single node was 
  visited (ensuring the graph isn't broken into disconnected pieces).
=======================================================================================
*/

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        
        // Mathematical shortcut: A tree must have exactly n - 1 edges
        if (edges.size() != n - 1) return false;

        vvii adj(n);
        for(auto& e : edges){
            adj[e[0]].pb(e[1]);
            adj[e[1]].pb(e[0]);
        }

        vii vis(n, 0);
        bool cycle = false;

        auto dfs = [&](int u, int p, auto&& dfs) -> void {
            // Early exit if another branch already found a cycle
            if (cycle) return;
            
            vis[u] = 1;

            for(auto v : adj[u]){
                if(v == p) continue; // Don't look back at the parent
                
                if(vis[v] == 1) {
                    cycle = true; // Cycle detected!
                    return;
                }
                
                dfs(v, u, dfs);
            }
        };

        // Start DFS from node 0. The parent of the root is -1.
        dfs(0, -1, dfs);

        // If a cycle was flagged during the void DFS, it's not a tree
        if (cycle) return false;

        // Ensure all nodes were visited (checks if graph is fully connected)
        for(int i = 0; i < n; i++){
            if(vis[i] == 0) return false;
        }

        return true;
    }
};