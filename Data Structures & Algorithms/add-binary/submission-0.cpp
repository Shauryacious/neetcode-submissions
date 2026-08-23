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
PATTERN: Two Pointers with Carry Math
Time Complexity: O(max(N, M)) | Space Complexity: O(max(N, M)) to store the result
=======================================================================================
Explanation:
- We iterate backwards through both strings simultaneously.
- We safely convert the `char` to `int` by subtracting '0'.
- `sum % 2` gives us the current bit (0 or 1).
- `sum / 2` extracts the carry (0 or 1) for the next iteration.
- We MUST keep looping if `carry` > 0 to catch the final overflow bit.
=======================================================================================
*/

class Solution {
public:
    string addBinary(string a, string b) {
        string ans = "";
        
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        
        // Loop while either string has digits, OR we have an active carry
        while (i >= 0 || j >= 0 || carry > 0) {
            int sum = carry;
            
            // If pointer 'i' is valid, add its bit and move left
            if (i >= 0) {
                sum += a[i] - '0';
                i--;
            }
            
            // If pointer 'j' is valid, add its bit and move left
            if (j >= 0) {
                sum += b[j] - '0';
                j--;
            }
            
            // Append the remainder (the actual bit) to our string
            ans += to_string(sum % 2);
            
            // Update the carry for the next column
            carry = sum / 2;
        }
        
        // Because we appended right-to-left, we must reverse the final string
        reverse(all(ans));
        
        return ans;
    }
};