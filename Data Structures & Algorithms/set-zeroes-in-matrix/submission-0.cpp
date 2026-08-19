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
APPROACH 1: The Brute Force (Deep Copy)
Time Complexity: O(M * N * (M + N)) | Space Complexity: O(M * N)
=======================================================================================
Explanation:
- If we modify the matrix in place immediately, we won't know if a '0' was originally
  there or if we just added it. We would end up wiping out the entire matrix.
- To prevent this, we create a full, independent copy of the matrix.
- We read from the original matrix to find the zeroes, but we write the zeroes into 
  the copy.
- Finally, we overwrite the original matrix with our modified copy.
=======================================================================================
*/
class Solution1 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        // Allocate a full copy of the matrix
        vvii copy_mat = matrix;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                
                // Read from the original
                if (matrix[i][j] == 0) {
                    
                    // Write to the copy: Nuke the row
                    for (int c = 0; c < n; c++) copy_mat[i][c] = 0;
                    
                    // Write to the copy: Nuke the column
                    for (int r = 0; r < m; r++) copy_mat[r][j] = 0;
                }
            }
        }
        
        // Reassign the original to the copied result
        matrix = copy_mat;
    }
};

/*
=======================================================================================
APPROACH 2: The Better Approach (Row and Column Flags)
Time Complexity: O(M * N) | Space Complexity: O(M + N)
=======================================================================================
Explanation:
- We don't actually need to copy the whole matrix. We just need to remember *which* 
  rows and *which* columns contained a zero.
- We create two separate 1D arrays: `row_flags` and `col_flags`.
- In the first pass, if we see a zero, we flag its specific row and column as '1'.
- In the second pass, we check every cell. If either its row flag OR its col flag 
  was triggered, we turn that cell into a 0.
=======================================================================================
*/
class Solution2 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        // Two independent arrays to track the state
        vii row_flags(m, 0);
        vii col_flags(n, 0);
        
        // STEP 1: Mark the flags
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    row_flags[i] = 1;
                    col_flags[j] = 1;
                }
            }
        }
        
        // STEP 2: Nuke based on flags
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (row_flags[i] == 1 || col_flags[j] == 1) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};

/*
=======================================================================================
APPROACH 3: The Optimal Approach (In-Place Flagging)
Time Complexity: O(M * N) | Space Complexity: O(1)
=======================================================================================
Explanation:
- Why allocate new `row_flags` and `col_flags` when we can just use the first row 
  and the first column of the matrix itself?
- `col_zero` tracks if the 0th column itself needs to be zeroed out (preventing overlap 
  with the 0th row at matrix[0][0]).
- We sweep the inner matrix to process flags, then carefully zero out the 0th row 
  and 0th column at the very end to avoid destroying our flags too early.
=======================================================================================
*/
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(); 
        int n = matrix[0].size(); 

        int col_zero = 1;
        
        // STEP 1: Sweep and set flags in the 0th row and 0th col
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 0){
                    if(j == 0){
                       matrix[i][0] = 0; 
                       col_zero = 0; 
                    }
                    else{
                        matrix[0][j] = 0; 
                        matrix[i][0] = 0;
                    }
                }
            }
        }

        // STEP 2: Sweep the INNER matrix (indices 1 to N)
        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                if(matrix[i][0] == 0  || matrix[0][j] == 0){
                    matrix[i][j] = 0;
                }
            }
        }

        // STEP 3: Nuke the 0th row if required
        if(matrix[0][0] == 0){
            for(int j = 0; j < n; j++){
                matrix[0][j] = 0;
            }
        }

        // STEP 4: Nuke the 0th column if required
        if(col_zero == 0){
            for(int i = 0; i < m; i++){
                matrix[i][0] = 0;
            }
        }
    }
};