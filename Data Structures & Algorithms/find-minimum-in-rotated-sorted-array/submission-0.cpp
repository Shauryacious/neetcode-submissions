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
APPROACH: Two Halves Comparison
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition & Visualization:
- Imagine taking a sorted array, cutting it into two pieces, and swapping them.
  Original: [0, 1, 2, 4, 5, 6, 7]
  Rotated:  [4, 5, 6, 7, | 0, 1, 2]

- The array is now divided into two distinct halves:
  1. The Left Half  (4, 5, 6, 7)
  2. The Right Half (0, 1, 2)

- Crucial Observation: EVERY element in the Left Half is strictly greater than 
  EVERY element in the Right Half. The minimum element (0) is exactly the very 
  first element of the Right Half.

Binary Search Logic ("Which half am I in?"):
- We pick a `mid` point and compare it with the absolute last element of our 
  search space (`a[hi]`).

- CASE 1: a[mid] > a[hi] 
  Example: `mid` is 7, `hi` is 2.
  If our current number is bigger than the number at the very end, it is physically 
  impossible for us to be in the Right Half. We MUST be standing in the Left Half! 
  Since the minimum is the start of the Right Half, we must move right.
  Action: `lo = mid + 1`

- CASE 2: a[mid] <= a[hi] 
  Example: `mid` is 1, `hi` is 2.
  If our current number is smaller than or equal to the number at the very end, we 
  are already standing in the Right Half! The minimum element is either exactly 
  where we are standing, or it is somewhere to our left.
  Action: `hi = mid` (Notice we DO NOT do `mid - 1`, because `mid` itself could be the min!)

The "Infinite Loop" Trap:
- Because we are using `hi = mid` instead of `hi = mid - 1`, if we use our standard 
  `while (lo <= hi)`, the code will get stuck in an infinite loop at the very end 
  when `lo` equals `hi`. 
- To fix this, we simply use `while (lo < hi)`. The loop will perfectly terminate the 
  exact moment `lo` and `hi` crash into each other, pointing directly at the answer.
=======================================================================================
*/
class Solution {
public:
    int findMin(vector<int>& a) {
        int lo = 0;
        int hi = a.size() - 1;
        
        // We use lo < hi to prevent infinite loops since we do `hi = mid`
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            
            // Am I in the Left Half?
            if (a[mid] > a[hi]) {
                // The minimum MUST be to my right.
                lo = mid + 1;
            } 
            // Am I in the Right Half?
            else {
                // The minimum is either me, or someone to my left.
                hi = mid; 
            }
        }
        
        // When lo and hi converge, they point exactly at the minimum element
        return a[lo];
    }
};