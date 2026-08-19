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

// Define Constants
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define py cout<<"YES"<<nl
#define pn cout<<"NO"<<nl
#define pm cout<<"-1"<<nl

// Typedef
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef vector<pll> vpll;

#define vvpll vector<vpll>

/*
=======================================================================================
PATTERN: 2D Matrix Backtracking + O(1) Ledgers
Time Complexity: O(N!) | Space Complexity: O(N) for board, ledgers, and stack
=======================================================================================
Explanation:
- We process the board row by row. `row` tracks which row we are currently filling.
- In each row, we try every `col` from 0 to N-1.
- We consult our 3 Ledgers: `cols`, `diag1`, and `diag2`. 
- If a spot is safe, we TAKE it (place 'Q', mark ledgers), RECURSE to `row + 1`, 
  and BACKTRACK (remove 'Q', unmark ledgers).
- When `row == n`, we successfully placed N Queens. We save the board state.
=======================================================================================
*/

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vs> ans;
        
        // Initialize an empty N x N board filled with '.'
        vs board(n, string(n, '.'));
        
        // The 3 Ledgers
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // Tracks '\' diagonals: row - col + (n - 1)
        vector<bool> diag2(2 * n - 1, false); // Tracks '/' diagonals: row + col
        
        auto f = [&](int row, vs& board, auto && f) -> void {
            
            // Base Case: We placed a queen in every row!
            if (row == n) {
                ans.pb(board);
                return;
            }
            
            // Try placing a queen in every column of the current row
            for (int col = 0; col < n; col++) {
                
                // Calculate the exact ledger index for the two diagonals
                int d1 = row - col + n - 1;
                int d2 = row + col;
                
                // If this cell is safe from all past Queens
                if (!cols[col] && !diag1[d1] && !diag2[d2]) {
                    
                    // ==========================================
                    // TAKE
                    // ==========================================
                    board[row][col] = 'Q';
                    cols[col] = true;
                    diag1[d1] = true;
                    diag2[d2] = true;
                    
                    // ==========================================
                    // RECURSE (Move to the next row)
                    // ==========================================
                    f(row + 1, board, f);
                    
                    // ==========================================
                    // BACKTRACK
                    // ==========================================
                    board[row][col] = '.';
                    cols[col] = false;
                    diag1[d1] = false;
                    diag2[d2] = false;
                }
            }
        };
        
        // Start filling from row 0
        f(0, board, f);
        
        return ans;
    }
};