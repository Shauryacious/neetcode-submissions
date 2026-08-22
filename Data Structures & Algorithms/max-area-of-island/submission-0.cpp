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
PATTERN: 2D Grid DFS (Connected Components)
Time Complexity: O(M * N) | Space Complexity: O(M * N) for visited array + recursion
=======================================================================================
Explanation:
- We maintain a `visited` array to ensure we never count a cell twice.
- We use directional arrays `dr` and `dc` to cleanly loop through the 4 neighbors.
- The `dfs` function takes `size` by reference (`int&`). Every time DFS lands on a 
  valid, unvisited land cell, it increments this variable.
- We loop through every cell. If it's unvisited land, we trigger DFS and update `max_area`.
=======================================================================================
*/

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        
        // Dedicated visited structure as requested
        vvii visited(m, vii(n, 0));
        
        int max_area = 0;
        
        // Direction vectors for moving Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // DFS Lambda: Captures size by reference to accumulate area
        auto dfs = [&](int r, int c, int& size, auto&& dfs) -> void {
            // Mark as visited and increment the size tracker
            visited[r][c] = 1;
            size++;
            
            // Explore all 4 adjacent directions
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Bounds check + Unvisited check + Land check
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    if (grid[nr][nc] == 1 && !visited[nr][nc]) {
                        dfs(nr, nc, size, dfs);
                    }
                }
            }
        };
        
        // Traverse the entire grid
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // If we find an unvisited piece of land, explore the whole island
                if (grid[i][j] == 1 && !visited[i][j]) {
                    int current_size = 0; // Initialize size for this specific island
                    
                    dfs(i, j, current_size, dfs);
                    
                    // Update global maximum
                    max_area = max(max_area, current_size);
                }
            }
        }
        
        return max_area;
    }
};