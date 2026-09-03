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
APPROACH (Explicit 3-Part Method): Kadane's Max, Kadane's Min, and Total Sum
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
WHY NOT JUST APPEND THE ARRAY?
- If we append `[5, 5, 5]` to become `[5, 5, 5, 5, 5, 5]`, standard Kadane's will 
  highlight the entire 2N array and return 30. 
- But the max length of a subarray is N=3, so the real answer is 15. Standard Kadane's 
  has no "length limit" concept and will illegally swallow duplicate elements.

THE MATHEMATICAL INVERSION (Two Universes):
To avoid length limits, we break the problem into two parallel universes:
- Universe 1 (Normal Subarray): The best sequence is strictly in the middle. 
  Solution: Standard Kadane's Maximum Subarray.
- Universe 2 (Wrapped Subarray): The best sequence takes a prefix and a suffix.
  If we pick the edges, the elements we EXCLUDED form a contiguous block in the middle!
  To maximize the edges, we must MINIMIZE the middle.
  Solution: (Total Sum of Array) - (Kadane's Minimum Subarray).

THE ALL-NEGATIVE EDGE CASE:
- Example: nums = [-3, -2, -3]
- Kadane's Max = -2
- Kadane's Min = -8 (the whole array)
- Total Sum = -8
- Wrapped Sum = Total - Min = -8 - (-8) = 0.
- A sum of 0 means we picked an EMPTY array (we excluded everything). But subarrays 
  must be non-empty! If Max Subarray < 0, all numbers are negative, so we just return 
  the Max Subarray (-2).
=======================================================================================
*/

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& a) {
        int n = a.size();

        // ---------------------------------------------------------
        // PART 1: Calculate the Total Sum of the array
        // ---------------------------------------------------------
        int total_sum = 0;
        for (int i = 0; i < n; i++) {
            total_sum += a[i];
        }

        // ---------------------------------------------------------
        // PART 2: Find Maximum Subarray Sum (Standard Kadane's)
        // ---------------------------------------------------------
        int max_sum = -INF;
        int cur_max = 0;
        for (int i = 0; i < n; i++) {
            // Extend or Start fresh
            cur_max = max(a[i], cur_max + a[i]);
            max_sum = max(max_sum, cur_max);
        }

        // ---------------------------------------------------------
        // PART 3: Find Minimum Subarray Sum (Inverted Kadane's)
        // ---------------------------------------------------------
        int min_sum = INF;
        int cur_min = 0;
        for (int i = 0; i < n; i++) {
            // Extend or Start fresh (but hunting for the lowest negative)
            cur_min = min(a[i], cur_min + a[i]);
            min_sum = min(min_sum, cur_min);
        }

        // ---------------------------------------------------------
        // FINAL LOGIC: Combine the Universes & Handle the Edge Case
        // ---------------------------------------------------------
        // If max_sum is negative, the entire array consists of negative numbers.
        // Returning (Total - Min) would return 0 (an illegal empty subarray).
        if (max_sum < 0) {
            return max_sum;
        }

        // Return the best of the "Normal" universe vs the "Wrapped" universe
        return max(max_sum, total_sum - min_sum);
    }
};