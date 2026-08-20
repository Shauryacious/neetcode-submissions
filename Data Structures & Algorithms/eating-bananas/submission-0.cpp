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
Time Complexity: O(N log(Max Pile Size)) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- We set our binary search bounds: `low = 1` and `high = max element in piles`.
- We use a lambda `check(mid)` to see if Koko can finish all piles at speed `mid` 
  within `h` hours.
- We use `(p + target - 1) / target` to simulate ceiling division purely with integers.
- Note: `total_hours` can exceed a standard 32-bit int, so we use `long long`.
- If `check(mid)` is true, it means `mid` is a valid speed. We record it and try to 
  find an even smaller valid speed (`high = mid - 1`).
- If false, she is eating too slowly, so we must increase the speed (`low = mid + 1`).
=======================================================================================
*/

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        
        ll low = 1;
        // The absolute fastest she ever needs to eat is the size of the largest pile
        ll high = *max_element(all(piles));
        ll ans = high; 
        
        // Predicate function: Can Koko finish all bananas at 'target' speed within 'h' hours?
        auto check = [&](ll target) -> bool {
            ll total_hours = 0;
            
            for (int p : piles) {
                // Integer ceiling division trick
                total_hours += (p + target - 1) / target;
            }
            
            return total_hours <= h;
        };
        
        // Binary Search
        while (low <= high) {
            ll mid = low + (high - low) / 2;
            
            if (check(mid)) {
                ans = mid;          // Record the valid eating speed
                high = mid - 1;     // Greedily hunt for an even slower valid speed
            } else {
                low = mid + 1;      // She was too slow, she must eat faster
            }
        }
        
        return ans;
    }
};