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
Time Complexity: O(log X) | Space Complexity: O(1)
=======================================================================================
*/

class Solution {
public:
    int mySqrt(int x) {
        // Edge case: Square root of 0 is 0
        if (x == 0) return 0;
        
        // Predicate function: Is the square of 'mid' <= x?
        auto check = [&](ll mid) -> bool {
            // Using long long prevents multiplication overflow for large guesses
            return mid * mid <= x;
        };
        
        ll low = 1;
        ll high = x;
        ll ans = 1;
        
        while (low <= high) {
            ll mid = low + (high - low) / 2;
            
            if (check(mid)) {
                ans = mid;          // Valid root, save it!
                low = mid + 1;      // MAXIMIZE: Try to find a larger valid root
            } else {
                high = mid - 1;     // Guess was too large, decrease it
            }
        }
        
        return (int)ans;
    }
};