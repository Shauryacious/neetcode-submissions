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
PATTERN: Binary Search on Answer
Time Complexity: O(N * log(Sum of Array)) | Space Complexity: O(1) auxiliary
Where N is the number of elements in `nums`.
=======================================================================================
EXPLANATION OF LOGIC:
- This is a mathematical clone of 'Allocate Minimum Pages'.
- `low`: The absolute minimum threshold must be at least the largest single element.
- `high`: The absolute maximum threshold needed is the sum of all elements (k=1).
- We use a lambda `check(capacity)` to greedily simulate splitting the array.
- We add elements to `current_sum`. Once adding the next element exceeds `capacity`, we 
  are forced to end the current subarray and start a new one (`subarrays_needed++`).
- If `subarrays_needed` exceeds `k`, the capacity is too small.
- If `subarrays_needed <= k`, the capacity is valid. We save it and hunt for a tighter, 
  smaller maximum (`high = mid - 1`).
=======================================================================================
*/

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int n = sz(nums);
        
        // Predicate function: Can we split the array into <= k subarrays 
        // such that no subarray exceeds 'capacity'?
        auto check = [&](ll capacity) -> bool {
            ll subarrays_needed = 1;
            ll current_sum = 0;
            
            for (int num : nums) {
                if (current_sum + num > capacity) {
                    // Current subarray is full. Start a new one.
                    subarrays_needed++;
                    current_sum = num;
                } else {
                    // Add to the current subarray.
                    current_sum += num;
                }
            }
            
            return subarrays_needed <= k;
        };
        
        // Binary Search bounds
        ll low = *max_element(all(nums));
        ll high = accumulate(all(nums), 0LL); 
        
        ll ans = high;
        
        while (low <= high) {
            ll mid = low + (high - low) / 2;
            
            if (check(mid)) {
                ans = mid;          // This threshold works, save it!
                high = mid - 1;     // Aggressively hunt for an even smaller max limit
            } else {
                low = mid + 1;      // Threshold was too tight, required too many subarrays
            }
        }
        
        return ans;
    }
};