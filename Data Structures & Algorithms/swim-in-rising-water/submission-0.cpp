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
PATTERN: Modified Dijkstra's Algorithm (Minimax / Bottleneck Path)
Time Complexity: O(N^2 log(N^2)) | Space Complexity: O(N^2)
=======================================================================================
Explanation:
- We use a Min-Heap (priority_queue) to always explore the adjacent cell with the 
  lowest overall bottleneck.
- The state in our PQ is {max_elevation_on_this_path, row, col}.
- Unlike standard Dijkstra where distance = `dist + weight`, here the distance metric 
  is `max(current_bottleneck, next_cell_elevation)`.
- We use a standard `visited` array because once we pop a cell from a Min-Heap, we 
  are guaranteed we found the optimal (lowest) bottleneck to reach it.
=======================================================================================
*/

class Solution1 {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Min-Heap stores vectors: {max_elevation_so_far, row, col}
        // `greater<vii>` ensures it sorts ascending by the first index (elevation)
        priority_queue<vii, vvii, greater<vii>> pq;
        
        vvii vis(n, vii(n, 0));
        
        // Start at top-left. The initial bottleneck is simply the starting cell's elevation.
        pq.push({grid[0][0], 0, 0});
        vis[0][0] = 1;
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!pq.empty()) {
            auto curr = pq.top();
            pq.pop();
            
            int t = curr[0]; // The highest peak we've had to cross so far
            int r = curr[1];
            int c = curr[2];
            
            // Because it's a Min-Heap, the first time we reach the end is the optimal answer.
            if (r == n - 1 && c == n - 1) {
                return t;
            }
            
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Bounds check and visited check
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !vis[nr][nc]) {
                    
                    vis[nr][nc] = 1; // Mark visited immediately to prevent duplicate pushes
                    
                    // The new bottleneck is whichever is higher: our current path's peak, 
                    // or the elevation of the specific cell we are stepping onto.
                    int next_bottleneck = max(t, grid[nr][nc]);
                    
                    pq.push({next_bottleneck, nr, nc});
                }
            }
        }
        
        return -1; 
    }
};

/*
=======================================================================================
PATTERN: Disjoint Set Union (The Flood-Fill Meeting Point)
Time Complexity: O(N^2 log(N^2)) | Space Complexity: O(N^2)
=======================================================================================
Explanation:
- We flatten the 2D grid into a 1D array of `edges` storing {elevation, row, col}.
- We sort the array so we process the grid strictly from lowest valley to highest peak.
- As we process each cell, we check its neighbors. If a neighbor has already been 
  submerged (its elevation is <= current), we connect them using DSU.
- We constantly check if the root of `(0,0)` is the same as the root of `(n-1, n-1)`. 
  The very first time this returns true, the start and end have met, and the 
  current elevation is our bottleneck answer.
=======================================================================================
*/

class DSU {
    vii parent, rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    
    void unite(int u, int v) {
        int ru = find(u), rv = find(v);
        if(ru == rv) return;
        if(rank[ru] > rank[rv]) parent[rv] = ru;
        else if(rank[rv] > rank[ru]) parent[ru] = rv;
        else {
            parent[rv] = ru;
            rank[ru]++;
        }
    }
    
    // Quick helper to see if the start and end have collided
    bool connected(int u, int v) {
        return find(u) == find(v);
    }
};

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        
        // Base case: If it's a 1x1 grid, the answer is just that cell's elevation
        if (n == 1) return grid[0][0];
        
        // {elevation, r, c}
        vvii cells;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cells.pb({grid[i][j], i, j});
            }
        }
        
        // Sort by elevation ascending
        sort(all(cells));
        
        // DSU sized for the flattened 1D grid (N * N)
        DSU dsu(n * n);
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Process cells from lowest elevation to highest
        for (auto& cell : cells) {
            int elevation = cell[0];
            int r = cell[1];
            int c = cell[2];
            
            // Flatten the 2D coordinate into a 1D ID for the DSU
            int u = r * n + c;
            
            // Try to connect to all 4 neighbors
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    // Only connect if the neighbor's elevation is <= our current water level
                    if (grid[nr][nc] <= elevation) {
                        int v = nr * n + nc;
                        dsu.unite(u, v);
                    }
                }
            }
            
            // The Start and End "Meeting Point" condition!
            int start_node = 0;
            int end_node = (n * n) - 1;
            
            if (dsu.connected(start_node, end_node)) {
                return elevation;
            }
        }
        
        return -1;
    }
};