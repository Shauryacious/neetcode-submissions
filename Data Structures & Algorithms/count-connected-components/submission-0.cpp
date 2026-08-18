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
APPROACH 1: Void DFS (Connected Components)
Time Complexity: O(V + E) | Space Complexity: O(V + E)
=======================================================================================
Explanation:
- We build an adjacency list for the undirected graph.
- We loop through every node. If `vis[i] == 0`, we found a new component!
- We increment our counter and fire the `void dfs` to mark the entire component as 1.
=======================================================================================
*/

class Solution1 {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vvii adj(n);
        for(auto& e : edges){
            adj[e[0]].pb(e[1]);
            adj[e[1]].pb(e[0]);
        }

        vii vis(n, 0);
        int ans = 0;

        // Your signature void dfs
        auto dfs = [&](int u, auto&& dfs) -> void {
            vis[u] = 1;
            for(auto v : adj[u]){
                if(vis[v] == 0){
                    dfs(v, dfs);
                }
            }
        };

        for(int i = 0; i < n; i++){
            // If we find an unvisited node, it's a new island
            if(vis[i] == 0){
                ans++;
                dfs(i, dfs); // Sink the island
            }
        }

        return ans;
    }
};

/*
=======================================================================================
APPROACH 2: Disjoint Set Union (DSU)
Time Complexity: O(V + E * alpha(V)) | Space Complexity: O(V)
=======================================================================================
Explanation:
- We start assuming there are `n` separate components.
- For every edge, we attempt to unite the two nodes.
- If `unite` succeeds (they were in different sets), the two sets merge into one, 
  so we decrement our total component count.
=======================================================================================
*/

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vii parent(n);
        vii rank(n, 1);
        
        // Initially, every node is its own parent
        iota(all(parent), 0);
        
        // Start with maximum possible components
        int ans = n;

        // Path compression find
        auto find = [&](int i, auto&& find) -> int {
            if(parent[i] == i) return i;
            return parent[i] = find(parent[i], find);
        };

        // Union by rank
        auto unite = [&](int i, int j) -> bool {
            int root_i = find(i, find);
            int root_j = find(j, find);

            if(root_i == root_j) return false;

            if(rank[root_i] < rank[root_j]){
                swap(root_i, root_j);
            }
            
            parent[root_j] = root_i;
            rank[root_i] += rank[root_j];
            
            return true;
        };

        // Process all edges
        for(auto& e : edges){
            // If they merged successfully, total components drops by 1
            if(unite(e[0], e[1])){
                ans--;
            }
        }

        return ans;
    }
};