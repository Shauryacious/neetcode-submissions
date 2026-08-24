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
#define vvpii vector<vpii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define pll pair<ll, ll>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define all(x) (x).begin(), (x).end()
#define INF 1e18
#define ff first
#define ss second

/*
=======================================================================================
PATTERN: Two Pointers (Fast Reader / Slow Writer)
Time Complexity: O(N) | Space Complexity: O(1) in-place
=======================================================================================
CP FACT: WHY WE DO NOT NEED THREE POINTERS
In competitive programming, the number of pointers you need perfectly matches the 
number of "regions" you are sorting your array into. 
- If you are partitioning into 3 regions (e.g., sorting 0s, 1s, and 2s in the Dutch 
  National Flag algorithm), you strictly need 3 pointers.
- In this problem, we are partitioning the array into exactly 2 regions: elements we 
  want to KEEP, and garbage `val` elements we want to IGNORE. 
Therefore, exactly 2 pointers are required. The 3rd variable `k` is naturally 
generated as our final answer!
=======================================================================================
Explanation:
- `j` acts as our Slow Writer (and ultimately our `k` return value).
- `i` acts as our Fast Reader, scanning from 0 to N-1.
- Every time the Reader `i` finds a number that is NOT `val`, we write it to the 
  Writer's current position `j`.
- Then, we increment the Writer `j` to prepare for the next valid number.
- Any elements equal to `val` are simply bypassed by the Reader and eventually 
  overwritten by the Writer.
=======================================================================================
*/

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        
        int j = 0; // The Slow Writer Pointer (also tracks our 'k' valid count)
        
        // 'i' is the Fast Reader Pointer
        for (int i = 0; i < nums.size(); i++) {
            
            // If the Reader finds a valid element that belongs in our "KEEP" region
            if (nums[i] != val) {
                
                // Write it to the 'j' position
                nums[j] = nums[i];
                
                // Move the Writer forward
                j++;
            }
        }
        
        // At the end, 'j' has advanced exactly 'k' times
        return j;
    }
};