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
APPROACH: "Perfect Half" Identification + Duplicate Blind Spot Handling
Time Complexity: O(log N) average, O(N) worst case | Space Complexity: O(1)
=======================================================================================
Intuition & Visualization:
- Any rotated sorted array can be split at `mid` into two halves. At least ONE of 
  these halves will always be perfectly sorted.
- Once we find the perfectly sorted half, we can easily check if our target mathematically 
  fits inside its boundaries (between its minimum and maximum).
  - If it fits, we throw away the messy half!
  - If it doesn't fit, it MUST be hiding in the messy half.

THE VILLAIN (Duplicates):
- If `a[lo] == a[mid] == a[hi]`, we hit a "Blind Spot". 
  Example: [3, 1, 2, 3, 3, 3, 3]. Here lo, mid, and hi are all 3. 
  Is the left half sorted? No, it's [3, 1, 2, 3]. 
  But `a[lo] <= a[mid]` (3 <= 3) is true! 
  Because of duplicates, the math lies to us. We must shrink the bounds until we can see clearly.
=======================================================================================
*/
class Solution {
public:
    bool search(vector<int>& a, int target) {
        int lo = 0;
        int hi = a.size() - 1;

        while (lo <= hi) {
            // Prevent integer overflow when calculating the middle index
            int mid = lo + (hi - lo) / 2;

            // JACKPOT: We found the target!
            if (a[mid] == target) {
                return true; 
            }

            // ====================================================================
            // THE BLIND SPOT (Duplicate Handling)
            // ====================================================================
            // If the ends and the middle are exactly the same, we have no idea 
            // which half is perfectly sorted. 
            // However, since we already checked `a[mid] == target` above and it was 
            // false, we 100% know that a[lo] and a[hi] are ALSO NOT the target.
            // Safe Action: Throw them away by stepping inward (lo++ and hi--).
            if (a[lo] == a[mid] && a[mid] == a[hi]) {
                lo++;
                hi--;
                continue; // Skip the rest of the loop and recalculate `mid` with new bounds
            }

            // ====================================================================
            // SCENARIO A: Is the LEFT half perfectly sorted?
            // ====================================================================
            if (a[lo] <= a[mid]) {
                
                // Since it's perfectly sorted, we know exactly what's inside it.
                // Does our target fall between the smallest (a[lo]) and largest (a[mid])?
                if (a[lo] <= target && target <= a[mid]) {
                    hi = mid - 1; // Yes! It is here. Discard the messy right half.
                } 
                else {
                    lo = mid + 1; // No! It's too big/small to be here. Search the messy right half.
                }
            }
            
            // ====================================================================
            // SCENARIO B: The RIGHT half MUST be perfectly sorted.
            // ====================================================================
            else {
                
                // Does our target fall between the smallest (a[mid]) and largest (a[hi])?
                if (a[mid] <= target && target <= a[hi]) {
                    lo = mid + 1; // Yes! It is here. Discard the messy left half.
                } 
                else {
                    hi = mid - 1; // No! It's too big/small to be here. Search the messy left half.
                }
            }
        }

        // If the loop finishes and we never hit the JACKPOT, it doesn't exist.
        return false; 
    }
};