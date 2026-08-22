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
Time Complexity: O(M * N) | Space Complexity: O(M * N) (No visited array needed!)
=======================================================================================
Explanation:
- We scan the grid to count `fresh_cnt` and load all initial rotten oranges into `q`.
- If `fresh_cnt == 0` at the start, we return 0 immediately.
- We use the `sz` snapshot to process the grid exactly one minute (level) at a time.
- Modifying the grid in-place (`grid[nr][nc] = 2`) eliminates the need for a `vis` array.
- As soon as `fresh_cnt` hits 0, we immediately return the elapsed `minutes`.
=======================================================================================
*/

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        
        queue<pii> q;
        int fresh_cnt = 0;
        
        // Step 1: Count fresh oranges and push all rotten ones to the queue
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fresh_cnt++;
                } else if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }
        
        // Edge Case: If there are no fresh oranges to begin with, time is 0
        if (fresh_cnt == 0) return 0;
        
        int minutes = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Step 2: Multi-Source BFS level-by-level sweep
        while (!q.empty()) {
            int sz = q.size();
            minutes++; // A minute elapses for this entire wave of rotting
            
            for (int i = 0; i < sz; i++) {
                pii curr = q.front();
                q.pop();
                
                int r = curr.ff;
                int c = curr.ss;
                
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    
                    // If within bounds AND the orange is fresh
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        
                        grid[nr][nc] = 2; // Mark as rotten (acts as our visited flag)
                        fresh_cnt--;
                        
                        // ELITE OPTIMIZATION: If we just rotted the last orange, return now!
                        if (fresh_cnt == 0) return minutes;
                        
                        q.push({nr, nc});
                    }
                }
            }
        }
        
        // If the queue is empty but we still have fresh oranges, they are unreachable
        return -1;
    }
};