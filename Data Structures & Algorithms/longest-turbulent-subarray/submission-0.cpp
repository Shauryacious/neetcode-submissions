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
PATTERN: Explicit Sliding Window (`while` loop)
Time Complexity: O(N) | Space Complexity: O(1)
=======================================================================================
EXPLANATION OF LOGIC:
- Using a `while` loop cleanly separates the window evaluation from the pointer movement.
- Step 1: Calculate current step direction.
- Step 2: Adjust `left` anchor if the sequence is broken (flat or stutter).
- Step 3: Record the window length.
- Step 4: Save `curr_sign` into `prev_sign`.
- Step 5: Explicitly increment `right`.
=======================================================================================
*/

class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int n = sz(arr);
        if (n <= 1) return n;
        
        int left = 0;
        int right = 1;
        int max_len = 1;
        int prev_sign = 0; 
        
        while (right < n) {
            
            // 1. OBSERVE: Determine the direction of the current step
            int curr_sign = 0;
            if (arr[right] > arr[right - 1]) {
                curr_sign = 1;
            } else if (arr[right] < arr[right - 1]) {
                curr_sign = -1;
            }
            
            // 2. ADJUST LEFT: Fix the window if the turbulence broke
            if (curr_sign == 0) {
                // Flatline: collapse the tape measure completely
                left = right;
            } 
            else if (right > 1 && curr_sign == prev_sign) {
                // Stutter: shrink the tape measure to just the last two elements
                left = right - 1;
            }
            
            // 3. RECORD: The window [left, right] is guaranteed valid here
            max_len = max(max_len, right - left + 1);
            
            // 4. REMEMBER: Save state for the next cycle
            prev_sign = curr_sign;
            
            // 5. EXPAND: Explicitly move the right boundary forward
            right++;
        }
        
        return max_len;
    }
};