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
PATTERN: Binary Exponentiation (Iterative)
Time Complexity: O(log N) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- We cast `n` to a `long long` to safely handle `INT_MIN` inversion without overflow.
- If the exponent is negative, we invert `x` (x = 1/x) and make the exponent positive.
- While the power is > 0:
  1. If the power is odd, we multiply our running `ans` by the current `x`.
  2. We square `x` (x *= x) to prepare for the next order of magnitude.
  3. We divide the power by 2.
- This effectively calculates powers by walking up their binary representation!
=======================================================================================
*/

class Solution {
public:
    double myPow(double x, int n) {
        
        // 1. Cast to long long to prevent INT_MIN overflow
        ll power = n;
        
        // 2. Handle negative exponents mathematically
        if (power < 0) {
            x = 1.0 / x;
            power = abs(power);
        }
        
        double ans = 1.0;
        
        // 3. Binary Exponentiation loop
        while (power > 0) {
            
            // If the current power is odd, peel off one 'x' and multiply it into the answer
            if (power % 2 == 1) {
                ans *= x;
            }
            
            // Square the base for the next iteration
            x *= x;
            
            // Halve the power
            power /= 2;
        }
        
        return ans;
    }
};