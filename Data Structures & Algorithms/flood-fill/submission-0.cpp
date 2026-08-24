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
PATTERN: Connected Component DFS (The "Paint Bucket" Algorithm)
Time Complexity: O(M * N) | Space Complexity: O(M * N) for the recursive call stack
=======================================================================================
Explanation:
- We record the `original_color` of the starting pixel.
- We MUST check if `original_color == color` and exit early to prevent an infinite loop.
- The DFS changes the color of the current pixel to the new `color`. This implicitly 
  marks it as "visited", so we don't need an extra `vis` matrix!
- We use `dr` and `dc` direction arrays to cleanly explore all 4 cardinal directions.
=======================================================================================
*/

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int m = image.size();
        int n = image[0].size();
        
        int original_color = image[sr][sc];
        
        // Edge Case: If the color is already correct, do nothing to avoid infinite recursion
        if (original_color == color) {
            return image;
        }
        
        // Direction arrays: Up, Down, Left, Right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Lambda DFS capturing context by reference
        auto dfs = [&](int r, int c, auto&& dfs) -> void {
            
            // Paint the current pixel (this also acts as our 'visited' marker)
            image[r][c] = color;
            
            // Explore all 4 directions
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Bounds check AND check if the neighbor has the original color
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && image[nr][nc] == original_color) {
                    dfs(nr, nc, dfs);
                }
            }
        };
        
        // Launch the flood fill from the starting pixel
        dfs(sr, sc, dfs);
        
        return image;
    }
};