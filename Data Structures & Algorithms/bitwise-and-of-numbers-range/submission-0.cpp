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
PATTERN: Bit Manipulation (Common Prefix)
Time Complexity: O(1) [Max 32 iterations] | Space Complexity: O(1)
=======================================================================================
Explanation:
- We chop off the rightmost bits of both numbers until they are identical.
- Every time we chop, we increment `shift_count`.
- Once `left == right`, we have found the common binary prefix that survived the AND.
- We restore the magnitude by shifting the prefix left by `shift_count` zeros.
=======================================================================================
*/

class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift_count = 0;
        
        // Shift both numbers right until they match
        while (left != right) {
            left >>= 1;
            right >>= 1;
            shift_count++;
        }
        
        // Shift the common prefix back to its original position
        return left << shift_count;
    }
};