// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>
#include<set>

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
APPROACH: Multiset (Min-Heap Simulation)
Time Complexity: O(N log K) | Space Complexity: O(K)
=======================================================================================
Intuition & Visualization:
- We use a default `multiset` which sorts in ascending order.
- As we iterate through `nums`, we insert each number into the multiset.
- If the size exceeds `k`, we erase the element at `ms.begin()`. Since the set is 
  ascending, this mathematically guarantees we are always throwing away the smallest 
  element currently in our pool.
- At the end of the loop, the multiset contains strictly the `k` largest elements.
- The smallest of these `k` elements (the kth largest overall) is sitting right 
  at `ms.begin()`.
=======================================================================================
*/
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int> ms;
        
        for (int num : nums) {
            // Let the number into the VIP club
            ms.insert(num);
            
            // If the club is overcrowded, kick out the smallest number
            if (ms.size() > k) {
                ms.erase(ms.begin());
            }
        }
        
        // The weakest of the remaining elite is the Kth largest
        return *ms.begin();
    }
};


/*
=======================================================================================
APPROACH: Quickselect (Hoare's / Lomuto Partitioning)
Time Complexity: O(N) Average, O(N^2) Worst | Space Complexity: O(1) Auxiliary
=======================================================================================
Intuition & Visualization:
- The K-th largest element is the (N - K)-th smallest element. Let's call this `target`.
- We define a window `[left, right]` and pick a random pivot to partition the array.
- `partition` moves all elements <= pivot to the left, and > pivot to the right.
- It returns `p`, which is the absolute final sorted index of our pivot.
- If `p == target`, we found our element!
- If `p < target`, our target is to the right. We update `left = p + 1`.
- If `p > target`, our target is to the left. We update `right = p - 1`.
=======================================================================================
*/
class Solution2 {
private:
    int partition(vector<int>& nums, int left, int right) {
        // 1. Pick a random pivot to avoid O(N^2) worst-case on sorted arrays
        int rand_idx = left + rand() % (right - left + 1);
        swap(nums[rand_idx], nums[right]);
        
        int pivot = nums[right];
        int p = left; // This pointer tracks where the next smaller element should go
        
        // 2. Push all elements smaller than the pivot to the left side
        for (int i = left; i < right; i++) {
            if (nums[i] <= pivot) {
                swap(nums[p], nums[i]);
                p++;
            }
        }
        
        // 3. Place the pivot exactly on the boundary line
        swap(nums[p], nums[right]);
        
        // Return the final, absolute sorted index of the pivot
        return p;
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int target_index = n - k; // Convert K-th largest to K-th smallest index
        
        int left = 0;
        int right = n - 1;
        
        // Iterative Quickselect for strictly O(1) space
        while (left <= right) {
            int pivot_index = partition(nums, left, right);
            
            if (pivot_index == target_index) {
                return nums[pivot_index];
            } 
            else if (pivot_index < target_index) {
                left = pivot_index + 1;  // Search the right half
            } 
            else {
                right = pivot_index - 1; // Search the left half
            }
        }
        
        return -1;
    }
};
