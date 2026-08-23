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
PATTERN: Bitwise Injection (Blank Canvas)
Time Complexity: O(log(x) + log(n)) ≈ O(1) | Space Complexity: O(1)
=======================================================================================
Explanation:
- The base number `ans` starts as `x`. We cannot alter any of its `1` bits.
- We need the `(n - 1)`-th valid number, so we will inject the bits of `(n - 1)` 
  into the `0` positions of `ans`.
- `target_bits = n - 1`.
- We use a pointer `bit_pos` to scan through `ans` from right to left (bit 0 to 63).
- If the bit at `bit_pos` in `ans` is `0`, it is an empty slot! We take the rightmost 
  bit of `target_bits`, place it there, and shift `target_bits` to the right to 
  prepare the next bit for injection.
=======================================================================================
*/

class Solution {
public:
    long long minEnd(int n, int x) {
        
        // We must use long long because the answer can exceed 32 bits
        long long ans = x;
        long long target_bits = n - 1;
        
        long long bit_pos = 0; // Tracks which bit position in `ans` we are looking at
        
        // As long as we still have bits of (n-1) left to inject...
        while (target_bits > 0) {
            
            // If the current bit position in 'ans' is a 0 (an empty slot)
            if ((ans & (1LL << bit_pos)) == 0) {
                
                // Grab the rightmost bit of our target
                long long bit_to_inject = target_bits & 1;
                
                // If the bit to inject is 1, flip the empty 0 slot to 1
                if (bit_to_inject == 1) {
                    ans |= (1LL << bit_pos);
                }
                
                // Shift target_bits right because we just successfully injected a bit
                target_bits >>= 1;
            }
            
            // Move our scanner to the next bit to the left
            bit_pos++;
        }
        
        return ans;
    }
};