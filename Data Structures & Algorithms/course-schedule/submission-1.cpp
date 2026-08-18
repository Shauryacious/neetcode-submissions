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
APPROACH 1: DFS with Graph Coloring (3 States)
Time Complexity: O(V + E) | Space Complexity: O(V + E) for Adjacency List & Recursion
=======================================================================================
Explanation:
- We build a directed graph where Edge B -> A means "B is a prerequisite for A".
- We run a DFS using a 3-state `vis` array to track the recursion stack.
- Hitting a node marked `1` means we found a back-edge (a cycle).
- If a node is marked `2`, it was already proven safe, so we skip it to save time.
=======================================================================================
*/

class Solution1 {
public:
    bool canFinish(int n, vector<vector<int>>& edges) {
        vvii adj(n);
        for(auto e : edges){
            // e[1] is the prerequisite for e[0]
            int a = e[0], b = e[1];
            adj[b].pb(a); // Directed edge from b -> a
        }

        // 0 = unvisited
        // 1 = in current path
        // 2 = completely visited and safe
        vii vis(n, 0);
        bool cycle = false;

        auto dfs = [&](int u, auto && dfs) -> void {
            // If the same node is being visited in the current path, there is a cycle!
            if(vis[u] == 1){
                cycle = true;
                return;
            }
            
            // Mark as part of the current exploration path
            vis[u] = 1;

            for(auto v : adj[u]){
                if(vis[v] == 2) continue; // Already proven safe
                if(cycle) return;         // Early exit if cycle already found
                dfs(v, dfs);
            }

            // Completely visited this node, will never visit it again in the same path
            vis[u] = 2;
        };

        for(int u = 0; u < n; u++){
            if(cycle) return false;
            if(vis[u] == 0){
                dfs(u, dfs);
            }
        }

        return !cycle; // If no cycle, we can finish!
    }
};

/*
=======================================================================================
APPROACH 2: BFS (Kahn's Algorithm for Topological Sort)
Time Complexity: O(V + E) | Space Complexity: O(V + E)
=======================================================================================
Explanation:
- We calculate the `indeg` (number of incoming prerequisite edges) for every node.
- Nodes with 0 prerequisites are pushed into a queue.
- As we process a node, we "complete" it, stripping away its outgoing dependencies 
  by decrementing the `indeg` of its neighbors.
- If a neighbor hits 0, it unlocks, and we queue it.
- If we manage to pop N courses, we succeeded!
=======================================================================================
*/

class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& pre) {
        vvii adj(n);
        vii indeg(n, 0);

        for(auto p : pre){
            int a = p[0], b = p[1];
            adj[b].pb(a); // b -> a
            indeg[a]++;
        }

        vii topo;
        queue<int> q;

        // Push all initially unlocked courses (0 prerequisites)
        for(int i = 0; i < n; i++) {
            if(indeg[i] == 0) {
                q.push(i);
            }
        }

        while(!q.empty()) {
            int u = q.front();
            q.pop();
            topo.pb(u);

            // Complete the course and unlock dependent courses
            for(auto v : adj[u]) {
                indeg[v]--;
                if(indeg[v] == 0) {
                    q.push(v);
                }
            }
        }

        // If we processed all 'n' nodes, there were no cyclic deadlocks!
        return topo.size() == n;
    }
};