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
PATTERN: DFS Boundary Counting (with Direction Arrays)
Time Complexity: O(R * C) | Space Complexity: O(R * C) 
=======================================================================================
Explanation:
- We set up `dr` and `dc` arrays to represent the 4 cardinal directions.
- The `nr` and `nc` variables dynamically calculate the next cell to step onto.
- If that step goes out of bounds or hits water, it counts as 1 perimeter edge.
- If it's unvisited land, the DFS continues recursively into that new cell.
=======================================================================================
*/

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        
        vvii vis(row, vii(col, 0));
        int ans = 0; 
        
        // Direction arrays: Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Lambda DFS capturing 'ans', 'grid', 'vis', 'row', 'col', 'dr', 'dc'
        auto dfs = [&](int r, int c, auto&& dfs) -> void {
            
            // Condition 1: Out of bounds or hit water -> This is an edge!
            if (r < 0 || r >= row || c < 0 || c >= col || grid[r][c] == 0) {
                ans++;
                return;
            }
            
            // Condition 2: Already visited land
            if (vis[r][c] == 1) {
                return;
            }
            
            // Mark current cell as visited
            vis[r][c] = 1;
            
            // Loop through all 4 directions using dr and dc
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                dfs(nr, nc, dfs);
            }
        };
        
        // Scan the grid to find the island
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                
                if (grid[i][j] == 1) {
                    // Start the DFS traversal
                    dfs(i, j, dfs);
                    
                    // Since there is strictly only one island, we are done
                    return ans;
                }
            }
        }
        
        return 0;
    }
};