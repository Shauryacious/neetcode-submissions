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
PATTERN: Binary Search on Partitions
Time Complexity: O(log(min(m, n))) | Space Complexity: O(1)
=======================================================================================
EXPLANATION OF LOGIC:
- Always run the binary search on the smaller array to prevent Index Out of Bounds on 
  the second array's calculated partition.
- `cut1` is the number of elements we take from `nums1` for the left half.
- `cut2` is strictly calculated so the total left half contains `(m + n + 1) / 2` elements.
- We extract the 4 bordering elements (`l1`, `l2`, `r1`, `r2`). If a cut happens at the 
  very edge (0 or size), we substitute with INT_MIN or INT_MAX to safely bypass checks.
- Cross check: if `l1 <= r2` and `l2 <= r1`, the partition is valid!
- If the total length is odd, the median is the max of the left half.
- If even, the median is the average of the max of left half and min of right half.
=======================================================================================
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = sz(nums1);
        int n = sz(nums2);
        
        // Optimization & Safety: Ensure we always binary search on the smaller array
        if (m > n) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int low = 0;
        int high = m;
        int total_left_elements = (m + n + 1) / 2;
        
        while (low <= high) {
            // How many elements to take from the smaller array (nums1)
            int cut1 = low + (high - low) / 2;
            
            // Forced number of elements to take from the larger array (nums2)
            int cut2 = total_left_elements - cut1;
            
            // Extract the 4 edge elements surrounding the cuts.
            // If the cut is at index 0, there is no left element (use INT_MIN).
            // If the cut is at the array's end, there is no right element (use INT_MAX).
            int l1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
            int l2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
            int r1 = (cut1 == m) ? INT_MAX : nums1[cut1];
            int r2 = (cut2 == n) ? INT_MAX : nums2[cut2];
            
            // Validate the cross-diagonals
            if (l1 <= r2 && l2 <= r1) {
                // The perfect cut has been found!
                
                // If total length is ODD, median is simply the largest element on the left
                if ((m + n) % 2 != 0) {
                    return max(l1, l2);
                } 
                // If total length is EVEN, median is the average of the two middle elements
                else {
                    return (max(l1, l2) + min(r1, r2)) / 2.0;
                }
            } 
            else if (l1 > r2) {
                // We took too many elements from nums1. Move the cut left.
                high = cut1 - 1;
            } 
            else {
                // l2 > r1: We took too few elements from nums1. Move the cut right.
                low = cut1 + 1;
            }
        }
        
        return 0.0; // Fallback, though the loop is guaranteed to return mathematically
    }
};