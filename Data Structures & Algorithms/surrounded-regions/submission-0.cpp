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
PATTERN: Boundary Flood-Fill (Reverse Thinking DFS)
Time Complexity: O(M * N) | Space Complexity: O(M * N) auxiliary for recursion stack
=======================================================================================
Explanation:
- PHASE 1: We loop through the perimeter (first/last row, first/last column).
- If we find an 'O' on the perimeter, it is safe. We trigger a DFS to mark it and all 
  connected 'O's as '#'. This inherently acts as our visited state.
- PHASE 2: We sweep the entire board once. 
  - If a cell is 'O', it means the DFS never reached it, so it is surrounded. Change it to 'X'.
  - If a cell is '#', it means it was connected to the border. Restore it back to 'O'.
=======================================================================================
*/

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        
        int m = board.size();
        int n = board[0].size();
        
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // DFS to mark all safe 'O's as '#'
        auto dfs = [&](int r, int c, auto&& dfs) -> void {
            board[r][c] = '#';
            
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && board[nr][nc] == 'O') {
                    dfs(nr, nc, dfs);
                }
            }
        };
        
        // Step 1: Traverse the left and right borders
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') dfs(i, 0, dfs);
            if (board[i][n - 1] == 'O') dfs(i, n - 1, dfs);
        }
        
        // Step 2: Traverse the top and bottom borders
        for (int j = 0; j < n; j++) {
            if (board[0][j] == 'O') dfs(0, j, dfs);
            if (board[m - 1][j] == 'O') dfs(m - 1, j, dfs);
        }
        
        // Step 3: Final sweep to flip the remaining characters
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X'; // Captured!
                } else if (board[i][j] == '#') {
                    board[i][j] = 'O'; // Safe, restore it
                }
            }
        }
    }
};