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
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e9 
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
#define all(x) (x).begin(), (x).end()

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
PATTERN: 2D Binary Search (Virtual Flattening)
Time Complexity: O(log(M * N)) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- We treat the 2D matrix as a 1D array with indices from `0` to `(m * n) - 1`.
- We run a standard binary search on this virtual 1D range.
- Inside the loop, we convert our 1D `mid` index back to a 2D matrix coordinate using:
  - Row = `mid / columns`
  - Col = `mid % columns`
- We then just compare the value and shrink our binary search bounds accordingly!
=======================================================================================
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
        // Edge case: Empty matrix
        if (matrix.empty() || matrix[0].empty()) return false;
        
        int m = sz(matrix);
        int n = sz(matrix[0]);
        
        // Our virtual 1D array boundaries
        int low = 0;
        int high = (m * n) - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // Map the 1D mid index to its actual 2D coordinates
            int row = mid / n;
            int col = mid % n;
            int mid_val = matrix[row][col];
            
            if (mid_val == target) {
                return true;
            } else if (mid_val < target) {
                low = mid + 1; // Target is in the right half
            } else {
                high = mid - 1; // Target is in the left half
            }
        }
        
        return false;
    }
};