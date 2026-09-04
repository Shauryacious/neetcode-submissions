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
SOLUTION 1: Brute Force (Append and Sort)
Time Complexity: O((M+N) log(M+N)) | Space Complexity: O(1) auxiliary space
=======================================================================================
EXPLANATION OF LOGIC:
1. Since `nums1` has enough trailing zeros to hold all of `nums2`, we can just copy 
   everything from `nums2` directly into the back of `nums1`.
2. Once the elements are together, we call `std::sort` on the entire array.
3. While correct and easy to write, this completely ignores the fact that both 
   arrays are already sorted, wasting operations.
=======================================================================================
*/

class Solution1 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // Overwrite the trailing zeros in nums1 with the elements of nums2
        for (int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        
        // Sort the entire combined array
        sort(all(nums1));
    }
};

/*
=======================================================================================
SOLUTION 2: Optimal (Backwards Two-Pointer)
Time Complexity: O(M + N) | Space Complexity: O(1) In-place
=======================================================================================
EXPLANATION OF LOGIC:
1. Pointer `i` starts at the last valid element of `nums1` (m - 1).
2. Pointer `j` starts at the last element of `nums2` (n - 1).
3. Pointer `k` starts at the absolute end of the `nums1` buffer (m + n - 1).
4. We compare `nums1[i]` and `nums2[j]`. The LARGER of the two gets placed at `nums1[k]`.
   By filling the array from right to left, we use the zero-buffer safely without 
   overwriting any unprocessed elements.
5. If `nums2` still has elements left after `nums1` is exhausted, we copy them over. 
   If `nums1` has elements left, they are already perfectly in place!
=======================================================================================
*/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;       // Pointer for the end of valid nums1 elements
        int j = n - 1;       // Pointer for the end of nums2
        int k = m + n - 1;   // Pointer for the absolute end of the nums1 buffer
        
        // While there are still elements in nums2 to merge
        while (j >= 0) {
            // If nums1 still has elements AND its current element is strictly greater
            if (i >= 0 && nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                i--;
            } 
            else {
                // Otherwise, nums2 wins the comparison (or nums1 is completely exhausted)
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }
    }
};