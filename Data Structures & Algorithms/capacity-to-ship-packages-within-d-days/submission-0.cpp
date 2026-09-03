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
Time Complexity: O(N * log(Sum of Weights)) | Space Complexity: O(1) auxiliary
Where N is the number of packages.
=======================================================================================
EXPLANATION OF LOGIC:
- `low`: The absolute minimum capacity must be at least the heaviest single package.
- `high`: The absolute maximum capacity needed is the sum of all packages (1 day).
- We use a lambda `check(capacity)` to greedily simulate loading the ship. 
- We add weights to `curr_load` until it exceeds `capacity`. Once it does, we dispatch 
  the ship, increment `days_needed`, and place that weight onto the next day's ship.
- If `days_needed` exceeds `days`, the tested capacity is too small.
- If `check(mid)` returns true, we record `mid` as a valid answer and aggressively 
  search the left half (`high = mid - 1`) to find an even smaller valid capacity.
=======================================================================================
*/

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int n = weights.size();
    
        // Predicate function: Can we ship all packages within 'days' at 'capacity'?
        auto check = [&](ll capacity) -> bool {
            ll days_needed = 1; // We always need at least 1 day to ship
            ll curr_load = 0;
            
            for (int w : weights) {
                if (curr_load + w > capacity) {
                    // Ship is full for today. Dispatch and start a new day.
                    days_needed++;
                    curr_load = w; 
                } else {
                    // Still have room, load it up!
                    curr_load += w;
                }
            }
            
            return days_needed <= days;
        };
        
        // Binary Search
        ll low = *max_element(all(weights));
        ll high = accumulate(all(weights), 0);
        
        ll ans = high;

        while (low <= high) {
            ll mid = low + (high - low) / 2;
            
            if (check(mid)) {
                ans = mid;          // This capacity works, save it!
                high = mid - 1;     // Let's try to squeeze it into a smaller ship
            } else {
                low = mid + 1;      // Ship was too small, it took too many days
            }
        }
        
        return ans;
    }
};