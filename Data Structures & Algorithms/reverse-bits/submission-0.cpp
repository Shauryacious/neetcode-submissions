// Author : Shaurya Agrawal
// Linkedin: https://www.linkedin.com/in/shauryacious/
// Codeforces: https://codeforces.com/profile/Shauryacious
// Love you mumma <3

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstring>

using namespace std;

#define ii int
#define vii vector<int>
#define vvii vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pii>
#define pb push_back
#define MOD 1000000007
#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define all(x) (x).begin(), (x).end()
#define INF 1e9

/*
=======================================================================================
PATTERN: Bit Manipulation (Extraction and Shifting)
Time Complexity: O(1) strictly 32 operations | Space Complexity: O(1)
=======================================================================================
Explanation:
- We iterate exactly 32 times.
- `n & 1` isolates the rightmost bit.
- `ans << 1` shifts the answer left to make room for the new bit.
- `ans | bit` inserts the isolated bit.
- `n >>= 1` shifts the original number right to process the next bit.
=======================================================================================
*/

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        
        for (int i = 0; i < 32; i++) {
            // 1. Extract the rightmost bit of n
            int bit = n & 1;
            
            // 2. Shift ans to the left to make room, then insert the bit
            ans <<= 1;
            ans = (ans | bit);
            
            // 3. Shift n to the right to queue up the next bit
            n >>= 1;
        }
        
        return ans;
    }
};


/*
=======================================================================================
PATTERN: Lookup Table / Precomputed Cache (O(1) Optimization)
Time Complexity: O(1) strictly 4 operations | Space Complexity: O(1) for 256-size array
=======================================================================================
Explanation:
- We create a `cache` array of size 256. 
- In the constructor, we pre-fill it. For example, cache[1] (00000001) will store 128 (10000000).
- In `reverseBits`, we extract 8 bits at a time using `n & 0xff` (which is `11111111` in binary).
- We look up the reversed 8 bits in the cache.
- We shift the reversed chunks into their mirrored positions (24, 16, 8, and 0).
=======================================================================================
*/

class Solution2 {
private:
    int cache[256];
    
    // Helper function to reverse a single 8-bit byte
    int reverseByte(int byte) {
        int rev = 0;
        for (int i = 0; i < 8; i++) {
            rev = (rev << 1) | (byte & 1);
            byte >>= 1;
        }
        return rev;
    }

public:
    // Constructor: Builds the lookup table exactly ONCE when the class is instantiated
    Solution2() {
        for (int i = 0; i < 256; i++) {
            cache[i] = reverseByte(i);
        }
    }

    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        
        // 1. Extract 1st byte (rightmost), reverse it, shift it 24 spaces left
        int byte1 = n & 0xff;
        ans |= (cache[byte1] << 24);
        n >>= 8;
        
        // 2. Extract 2nd byte, reverse it, shift it 16 spaces left
        int byte2 = n & 0xff;
        ans |= (cache[byte2] << 16);
        n >>= 8;
        
        // 3. Extract 3rd byte, reverse it, shift it 8 spaces left
        int byte3 = n & 0xff;
        ans |= (cache[byte3] << 8);
        n >>= 8;
        
        // 4. Extract 4th byte (leftmost), reverse it, leave it on the far right
        int byte4 = n & 0xff;
        ans |= (cache[byte4]);
        
        return ans;
    }
};