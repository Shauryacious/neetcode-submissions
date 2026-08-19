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
PATTERN: Array Hashing / State Tracking
Time Complexity: O(1) strictly 81 cells | Space Complexity: O(1) fixed arrays
=======================================================================================
Explanation:
- We create boolean matrices to act as our "ledgers" for rows, columns, and boxes.
- `rows[i][num]` is true if `num` has been seen in row `i`.
- `cols[j][num]` is true if `num` has been seen in column `j`.
- `boxes[i/3][j/3][num]` is true if `num` has been seen in that specific 3x3 box.
- We traverse the 9x9 board exactly once. If we encounter a number that is already 
  marked 'true' in ANY of its three ledgers, the Sudoku is invalid.
=======================================================================================
*/

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        
        // Our ledgers. Initialized to false (0).
        // The first dimension is the row/col/box index.
        // The second dimension is the digit (0 to 9, we ignore index 0).
        bool rows[9][10] = {false};
        bool cols[9][10] = {false};
        
        // 3D array for boxes: [box_row][box_col][digit]
        bool boxes[3][3][10] = {false};
        
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                
                // Skip empty cells
                if (board[i][j] == '.') continue;
                
                // Convert the char '1'-'9' into an actual integer 1-9
                int num = board[i][j] - '0';
                
                // Calculate the 2D coordinates of the 3x3 box
                int box_row = i / 3;
                int box_col = j / 3;
                
                // CHECK PHASE: Has this number violated any rules?
                if (rows[i][num] == true || 
                    cols[j][num] == true || 
                    boxes[box_row][box_col][num] == true) {
                    
                    return false; // Conflict detected!
                }
                
                // RECORD PHASE: Mark this number as seen in all three ledgers
                rows[i][num] = true;
                cols[j][num] = true;
                boxes[box_row][box_col][num] = true;
            }
        }
        
        // If we processed all 81 cells without returning false, it is valid!
        return true;
    }
};