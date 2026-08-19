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
#define INF 1e18
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
PATTERN: Digit-wise Math with Pre-emptive Overflow Checks
Time Complexity: O(log10(x)) | Space Complexity: O(1) strictly 32-bit compliant
=======================================================================================
Explanation:
- We extract the last digit using `x % 10`.
- We remove the last digit from `x` using `x / 10`.
- BEFORE we push the digit onto our `rev` integer (`rev = rev * 10 + digit`), we 
  ensure that doing so won't exceed standard 32-bit boundaries.
- If `rev` is already larger than `INT_MAX / 10`, multiplying it by 10 will overflow.
- If `rev` exactly equals `INT_MAX / 10`, we must check if the incoming digit exceeds 7 
  (since INT_MAX ends in 7). 
- We do the mirrored checks for INT_MIN (which ends in -8).
=======================================================================================
*/

class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        
        while (x != 0) {
            // Extract the rightmost digit (preserves sign in C++)
            int digit = x % 10;
            
            // Remove the rightmost digit from x
            x /= 10;
            
            // Pre-emptive Overflow Check for Positive Numbers
            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && digit > 7)) {
                return 0;
            }
            
            // Pre-emptive Underflow Check for Negative Numbers
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && digit < -8)) {
                return 0;
            }
            
            // Safe to push the digit
            rev = (rev * 10) + digit;
        }
        
        return rev;
    }
};