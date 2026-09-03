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
APPROACH 1: Manual Binary Search 
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- We run a standard binary search using `lo` and `hi`.
- If we find the target (`nums[mid] == target`), we return `mid`.
- The magic happens when the target is NOT found. The loop will terminate when 
  `lo > hi`. At this exact moment, `lo` is beautifully resting on the exact index 
  where the target *should* have been!
- Why? Because `lo` is always pushed to `mid + 1` when elements are too small. It 
  naturally stops on the first element that is greater than the target.
=======================================================================================
*/
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
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

        return lo; // Target not found, 'lo' is the insertion point
    }
};

/*
=======================================================================================
APPROACH 2: STL `lower_bound` (The Perfect Match)
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- The problem asks for the index of the target if it exists, OR the index where it 
  should be inserted (which is just the first element strictly greater than it).
- This is literally the exact definition of `std::lower_bound`! 
- `lower_bound` returns an iterator to the first element `>= target`. 
- No extra checks are needed, we just return the converted index directly.
=======================================================================================
*/
class Solution2 {
public:
    int searchInsert(vector<int>& nums, int target) {
        return lower_bound(all(nums), target) - nums.begin();
    }
};

/*
=======================================================================================
APPROACH 3: STL `upper_bound` (Your Exact Logic)
Time Complexity: O(log N) | Space Complexity: O(1)
=======================================================================================
Intuition:
- `upper_bound` gives us the first element strictly `> target`.
- If the target exists in the array, `upper_bound` has stepped exactly one position 
  past it. We can check the previous element (`idx - 1`) and return it.
- If the target does NOT exist, then `upper_bound` is already pointing to the exact 
  spot where the target needs to be inserted!
- We just add `idx > 0` to ensure we don't accidentally check index `-1` when the 
  target is smaller than the entire array.
=======================================================================================
*/
class Solution3 {
public:
    int searchInsert(vector<int>& nums, int target) {
        int idx = upper_bound(all(nums), target) - nums.begin();
        
        // If the element right behind upper_bound is our target, return its index
        if (idx > 0 && nums[idx - 1] == target) {
            return idx - 1;
        }
        
        // Otherwise, the upper_bound index itself is our insertion point
        return idx;
    }
};