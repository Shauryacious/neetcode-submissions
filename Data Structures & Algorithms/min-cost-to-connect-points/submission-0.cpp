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
#define vvpii vector<vpii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define pll pair<ll, ll>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define all(x) (x).begin(), (x).end()
#define INF 1e18
#define ff first
#define ss second

/*
=======================================================================================
PATTERN: Kruskal's Algorithm (Minimum Spanning Tree)
Time Complexity: O(N^2 log(N)) | Space Complexity: O(N^2)
=======================================================================================

THE "VISITED" ARRAY TRAP vs. DSU (Why DSU is Mandatory):

Why can't we just use a `vector<bool> visited` to avoid cycles?
Imagine a map with 4 isolated cities: A, B, C, and D.
1. The smallest edge on the map is (A-B). We connect them and mark A and B as `visited`.
2. The next smallest edge is (C-D). We connect them and mark C and D as `visited`.
3. The next smallest edge is (B-C). 

If we rely on a `visited` array, we look at B (visited) and C (visited) and we 
would DISCARD the edge! But wait—A-B and C-D are currently two completely separate, 
disconnected islands. We absolutely NEED the (B-C) edge to bridge them together!

A simple `visited` array only tells us "this node has been touched." It CANNOT tell 
the difference between "visited in the SAME island" vs. "visited in a DIFFERENT island."

DSU (Disjoint Set Union) fixes this. It assigns an absolute "root" ID to every island.
When we check `dsu.unite(u, v)`, it compares their island IDs.
- If they have DIFFERENT roots, they are separate islands. We merge them safely.
- If they have the EXACT SAME root, they are already connected. Adding this edge 
  would create a useless cycle, so we discard it.
=======================================================================================
*/

class DSU {
    vii parent;
    vii rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i; 
        }
    }
    
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); 
    }
    
    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        // Cycle detected: They are already in the exact same island
        if (rootU == rootV) return false; 
        
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootV] > rank[rootU]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true; 
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        
        // Edge list format: {distance, node1_index, node2_index}
        vvii edges;
        
        // Step 1: Generate all N*(N-1)/2 edges
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int dist = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                edges.pb({dist, i, j});
            }
        }
        
        // Step 2: Greedily sort edges by distance ascending
        sort(all(edges));
        
        DSU dsu(n);
        int min_cost = 0;
        int edges_used = 0;
        
        // Step 3: Kruskal's magic
        for (auto& edge : edges) {
            int d = edge[0];
            int u = edge[1];
            int v = edge[2];
            
            // DSU handles the complex logic: Are they in different islands?
            // If yes, unite them and return true.
            if (dsu.unite(u, v)) {
                min_cost += d;
                edges_used++;
                
                // MST is perfectly formed when we have bridged all isolated nodes 
                // using exactly N - 1 edges
                if (edges_used == n - 1) {
                    break;
                }
            }
        }
        
        return min_cost;
    }
};