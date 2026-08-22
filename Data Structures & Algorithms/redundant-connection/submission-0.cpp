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
PATTERN: Disjoint Set Union (Union-Find with Path Compression & Rank)
Time Complexity: O(N * α(N)) ≈ O(N) | Space Complexity: O(N) for parent and rank arrays
=======================================================================================
Explanation:
- DSU tracks connected components.
- `find(x)` finds the absolute root of a set. Path compression flattens the tree 
  so future lookups are essentially O(1).
- `unite(u, v)` attaches the smaller tree to the root of the larger tree (Union by Rank).
- If `unite` returns false, it means `u` and `v` already share the same root, meaning 
  they are already connected. Adding an edge between them creates a cycle!
=======================================================================================
*/

class DSU {
    vii parent;
    vii rank;
public:
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; // Every node is initially its own parent
        }
    }
    
    // Find with Path Compression
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); 
    }
    
    // Union by Rank
    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        // If they have the same root, they are already connected! (Cycle detected)
        if (rootU == rootV) return false;
        
        // Attach the smaller rank tree under the higher rank tree
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootV] > rank[rootU]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        
        return true; // Successfully merged
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        DSU dsu(n);
        
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            
            // If unite returns false, adding this edge causes a cycle
            if (!dsu.unite(u, v)) {
                return edge;
            }
        }
        
        return {};
    }
};