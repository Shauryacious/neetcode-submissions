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
PATTERN: Reverse Grid DFS (Multi-Source Concept)
Time Complexity: O(M * N) | Space Complexity: O(M * N) for the visited arrays
=======================================================================================
Explanation:
- We track two boolean matrices, `pac` and `atl`.
- We launch DFS from the coastlines.
- REVERSE RULE: A neighbor is valid if `heights[nr][nc] >= heights[r][c]`.
- Finally, any cell where `pac[i][j] == 1 && atl[i][j] == 1` is added to the answer.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();
        
        vvii ans;
        
        // Visited arrays acting as our two separate floods
        vvii pac(n, vii(m, 0));
        vvii atl(n, vii(m, 0));
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Pass the visited array by reference so we can reuse this lambda for both oceans
        auto dfs = [&](int r, int c, vvii& vis, auto&& dfs) -> void {
            vis[r][c] = 1;
            
            for(int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Boundary check
                if(nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    // Check if unvisited AND follows the reverse height rule (climbing up)
                    if(!vis[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                        dfs(nr, nc, vis, dfs);
                    }
                }
            }
        };
        
        // 1. Launch DFS from the Left and Right coastlines (Iterate over Rows)
        for(int i = 0; i < n; i++) {
            dfs(i, 0, pac, dfs);         // Left edge -> Pacific
            dfs(i, m - 1, atl, dfs);     // Right edge -> Atlantic
        }
        
        // 2. Launch DFS from the Top and Bottom coastlines (Iterate over Columns)
        for(int j = 0; j < m; j++) {
            dfs(0, j, pac, dfs);         // Top edge -> Pacific
            dfs(n - 1, j, atl, dfs);     // Bottom edge -> Atlantic
        }
        
        // 3. Find the intersection!
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // If water from both oceans reached here, add it to our result
                if(pac[i][j] == 1 && atl[i][j] == 1) {
                    ans.pb({i, j});
                }
            }
        }
        
        return ans;
    }
};