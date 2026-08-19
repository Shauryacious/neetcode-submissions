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
PATTERN: Boundary Shrinking Simulation
Time Complexity: O(M * N) strictly one pass | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- We track 4 boundaries: top, down, left, right.
- We peel the matrix in a standard 4-step sequence (Right, Down, Left, Up).
- After moving horizontally (Step 1), we shrink the `top` boundary.
- After moving vertically (Step 2), we shrink the `right` boundary.
- CRITICAL: Before Steps 3 and 4, we must verify the boundaries haven't crossed to 
  prevent duplicate printing on rectangular matrices.
=======================================================================================
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        int left = 0, right = n - 1; 
        int top = 0, down = m - 1; 

        vii ans;

        while (left <= right && top <= down) { 
            
            // Step 1 -> Move left to right in the top row
            for (int i = left; i <= right; i++) {
                ans.pb(mat[top][i]); 
            }
            top++; // The top row is finished, shrink the boundary down

            // Step 2 -> Move top to down in the rightmost column
            for (int i = top; i <= down; i++) {
                ans.pb(mat[i][right]); 
            }
            right--; // The right column is finished, shrink the boundary left

            // Step 3 -> Move from right to left in the bottom row
            // CHECK: Did the top boundary cross the down boundary in Step 1?
            if (top <= down) {
                for (int i = right; i >= left; i--) {
                    ans.pb(mat[down][i]); 
                }
                down--; // The bottom row is finished, shrink the boundary up
            }

            // Step 4 -> Move from down to top in the leftmost column
            // CHECK: Did the right boundary cross the left boundary in Step 2?
            if (left <= right) {
                for (int i = down; i >= top; i--) {
                    ans.pb(mat[i][left]); 
                }
                left++; // The left column is finished, shrink the boundary right
            }
        }
        
        return ans;
    }
};