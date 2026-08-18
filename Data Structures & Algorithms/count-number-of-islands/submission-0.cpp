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
PATTERN: Grid Connected Components (DFS / Flood Fill)
Time Complexity: O(M * N) | Space Complexity: O(M * N) for the recursion stack
=======================================================================================
Explanation:
- We iterate through every cell in the grid.
- Every time we encounter an unvisited land ('1'), we found a new island!
- We immediately increment our count, and launch a DFS to "sink" the entire island 
  by turning all connected '1's into '0's. This acts as our in-place visited array.
- We use standard `dr` and `dc` arrays for clean 4-directional traversal.
=======================================================================================
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        if(n == 0) return 0;
        int m = grid[0].size();
        
        int ans = 0;
        
        // Direction vectors for cleanly exploring Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        auto dfs = [&](int r, int c, auto&& dfs) -> void {
            // 1. Sink the current piece of land (Mark as visited)
            grid[r][c] = '0';
            
            // 2. Trust fall into all 4 directions
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Boundary checks AND check if it is land before recursing
                if(nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == '1') {
                    dfs(nr, nc, dfs);
                }
            }
        };
        
        // Scan the entire grid
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // Found an untouched island!
                if(grid[i][j] == '1') {
                    ans++; // Log the discovery
                    dfs(i, j, dfs); // Flood fill to sink it so we don't count it again
                }
            }
        }
        
        return ans;
    }
};