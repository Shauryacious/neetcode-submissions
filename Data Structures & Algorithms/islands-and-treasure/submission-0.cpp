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
PATTERN: Multi-Source BFS (Level-by-Level Sweep)
Time Complexity: O(M * N) | Space Complexity: O(M * N) for the queue
=======================================================================================
Explanation:
- We first sweep the grid and load every treasure chest (0) into the queue.
- We maintain a `dist` variable that increments exactly once after every level.
- `int sz = q.size();` takes a snapshot of the current wave. We process exactly `sz` 
  elements, mark their valid neighbors with `dist`, and push them for the next wave.
=======================================================================================
*/

class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return;
        
        int m = grid.size();
        int n = grid[0].size();
        
        const int EMPTY = INT_MAX; 
        
        queue<pii> q;
        
        // Step 1: Find all sources (treasure chests) and load them into the queue
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // We start looking for land that is exactly 1 step away from the chests
        int dist = 1;
        
        // Step 2: Level-by-level BFS expansion
        while (!q.empty()) {
            
            // Snapshot of the current wave
            int sz = q.size();
            
            // Process the entire wave before incrementing the distance
            for (int i = 0; i < sz; i++) {
                pii curr = q.front();
                q.pop();
                
                int r = curr.ff;
                int c = curr.ss;
                
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    
                    // Bounds check and unvisited empty land check
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == EMPTY) {
                        
                        grid[nr][nc] = dist; // Assign the current wave's distance
                        q.push({nr, nc});    // Queue for the next wave
                    }
                }
            }
            
            // Next wave will be one step further out
            dist++; 
        }
    }
};