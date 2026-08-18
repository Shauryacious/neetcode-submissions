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
PATTERN: Bit Manipulation (Hardware Adder)
Time Complexity: O(1) strictly <= 32 operations | Space Complexity: O(1)
=======================================================================================
Explanation:
- `a ^ b` computes the sum ignoring the carry.
- `(a & b) << 1` computes the carry. We cast to `unsigned int` to prevent C++ from 
  crashing on negative number shifts (Undefined Behavior).
- We repeat this process, adding the new carry to the raw sum, until no carry exists.
=======================================================================================
*/

class Solution {
public:
    int getSum(int a, int b) {
        
        // Loop until there is no carry left to add
        while (b != 0) {
            
            // 1. Calculate the carry (Bits where both a AND b are 1)
            // Cast to unsigned to avoid Undefined Behavior when shifting negative numbers
            int carry = (unsigned int)(a & b) << 1;
            
            // 2. Calculate the raw sum without the carry
            a = a ^ b;
            
            // 3. The carry becomes the new 'b' to be added to 'a' in the next iteration
            b = carry;
        }
        
        // When b (the carry) hits 0, a holds the complete sum
        return a;
    }
};