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
PATTERN: Dutch National Flag Algorithm (3 Pointers)
Time Complexity: O(N) Single Pass | Space Complexity: O(1) in-place
=======================================================================================
Explanation:
- `low` manages the 0s (Red) region.
- `high` manages the 2s (Blue) region.
- `mid` acts as the active scanner.
- We loop as long as `mid <= high`. Once `mid` crosses `high`, the entire array 
  is verified and sorted.
- Crucial logic: When swapping with `high`, DO NOT increment `mid`. The swapped 
  element needs to be evaluated on the next pass.
=======================================================================================
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0;
        int mid = 0;
        int high = nums.size() - 1;
        
        while (mid <= high) {
            if (nums[mid] == 0) {
                // Found a 0: Send it to the front boundary
                swap(nums[low], nums[mid]);
                low++;
                mid = max(mid, low); //mid should never be behind low
            } 
            else if (nums[mid] == 1) {
                // Found a 1: It's in the correct middle region, just move forward
                mid++;
            } 
            else if (nums[mid] == 2) {
                // Found a 2: Send it to the back boundary
                swap(nums[mid], nums[high]);
                high--;
                // mid++; // DO NOT increment mid! We must evaluate the newly swapped element.
            }
        }
    }
};