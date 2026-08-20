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
APPROACH 1: Manual Binary Search (The Core Algorithm)
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- We establish two pointers, `lo` and `hi`, representing our search boundaries.
- We repeatedly calculate the `mid` point as `lo + (hi - lo) / 2` to prevent integer 
  overflow if `lo` and `hi` are massive numbers.
- If `nums[mid]` is less than our target, the target MUST be to the right, so we 
  discard the left half by pulling `lo` forward to `mid + 1`.
- If `nums[mid]` is greater, the target MUST be to the left, so we discard the right 
  half by pulling `hi` back to `mid - 1`.
- If `lo` passes `hi` without finding the target, it doesn't exist.
=======================================================================================
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0;
        int hi = nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) {
                return mid; // Target found
            } 
            else if (nums[mid] < target) {
                lo = mid + 1; // Discard left half
            } 
            else {
                hi = mid - 1; // Discard right half
            }
        }

        return -1; // Target not found
    }
};

/*
=======================================================================================
APPROACH 2: STL `lower_bound` 
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- `lower_bound` returns an iterator to the FIRST element that is >= the target.
- We subtract `a.begin()` to convert that iterator into an integer index.
- If the target is larger than all elements in the array, `lower_bound` returns 
  `a.end()`, which means `idx == a.size()`. 
- To avoid crashing (Undefined Behavior), we MUST verify `idx < a.size()` before 
  we check if `a[idx] == target`.
=======================================================================================
*/
class Solution2 {
public:
    int search(vector<int>& a, int t) {
        // Find the index of the first element >= t
        int idx = lower_bound(all(a), t) - a.begin();
        
        // Safety check: is the index within bounds? AND does it actually match t?
        if (idx < a.size() && a[idx] == t) {
            return idx;
        }
        
        return -1;
    }
};

/*
=======================================================================================
APPROACH 3: STL `upper_bound` (The "One Step Back" Logic)
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- `upper_bound` returns an iterator to the FIRST element strictly GREATER than the target.
- Because the array is strictly sorted and contains unique elements, if the target 
  exists, it MUST sit exactly one position to the left of this upper bound!
- If the target is smaller than every element in the array, `upper_bound` will return 
  index 0. 
- We must check `idx > 0` to prevent an Out-Of-Bounds crash (accessing `a[-1]`), and 
  then we check if the element exactly behind the bound is our target.
=======================================================================================
*/
class Solution3 {
public:
    int search(vector<int>& a, int t) {
        // Find the index of the first element > t
        int idx = upper_bound(all(a), t) - a.begin();
        
        // The target (if it exists) must be exactly at idx - 1.
        // Safety check: ensure idx > 0 so we don't access a[-1].
        if (idx > 0 && a[idx - 1] == t) {
            return idx - 1;
        }
        
        return -1;
    }
};