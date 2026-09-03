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
PATTERN: Triple Binary Search
Time Complexity: O(log N) | Space Complexity: O(1)
API Calls: ~14*2 + ~14 + ~14 = ~56 calls (Well under the 100 limit for N=10000)
=======================================================================================
EXPLANATION OF LOGIC:
- Phase 1: Binary search to find the peak index. We use a predicate that returns true 
  if the current mid is strictly greater than the next element (meaning we are descending).
- Phase 2: Standard binary search on the ascending left half [0, peak].
- Phase 3: Reversed binary search on the descending right half [peak + 1, n - 1].
=======================================================================================
*/

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        
        // ==========================================
        // PHASE 1: Find the Peak Index
        // ==========================================
        // Predicate: Are we on the descending slope? (arr[mid] > arr[mid+1])
        auto check_peak = [&](int mid) -> bool {
            return mountainArr.get(mid) > mountainArr.get(mid + 1);
        };
        
        int low = 0;
        int high = n - 2; // -2 because we access mid + 1 inside the lambda
        int peak = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (check_peak(mid)) {
                peak = mid;         // Found a descending point, save it!
                high = mid - 1;     // MINIMIZE: We want the very first point it descends
            } else {
                low = mid + 1;      // We are still ascending, peak is to the right
            }
        }
        
        // ==========================================
        // PHASE 2: Search Ascending Left Slope
        // ==========================================
        low = 0;
        high = peak;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int mid_val = mountainArr.get(mid);
            
            if (mid_val == target) {
                return mid; // Since we search left side first, this is guaranteed minimum index
            } else if (mid_val < target) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        // ==========================================
        // PHASE 3: Search Descending Right Slope
        // ==========================================
        low = peak + 1;
        high = n - 1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int mid_val = mountainArr.get(mid);
            
            if (mid_val == target) {
                return mid;
            } else if (mid_val > target) {
                // WARNING: Array is DESCENDING here! 
                // If mid_val is too large, the smaller target is to the RIGHT.
                low = mid + 1; 
            } else {
                high = mid - 1;
            }
        }
        
        // If we reach here, the target doesn't exist in either half.
        return -1;
    }
};