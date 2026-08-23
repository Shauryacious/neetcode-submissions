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
PATTERN: 0-Indexed Base Conversion
Time Complexity: O(log_26(N)) | Space Complexity: O(log_26(N)) to store the string
=======================================================================================
Explanation:
- We loop as long as `columnNumber > 0`.
- We immediately subtract 1 to align the 1-based Excel system with 0-based modulo math.
- `rem = columnNumber % 26` gives us the exact alphabet offset (0 for A, 25 for Z).
- We convert the offset to a character by adding it to 'A'.
- We divide the remaining number by 26 to move to the next column digit.
- Since we built the string from right to left, we reverse it at the end.
=======================================================================================
*/

class Solution {
public:
    string convertToTitle(int columnNumber) {
        string ans = "";
        
        while (columnNumber > 0) {
            // Shift to 0-indexed to fix the "no zero digit" modulo trap
            columnNumber--; 
            
            // Get the current base-26 digit (0 to 25)
            int rem = columnNumber % 26;
            
            // Map 0 -> 'A', 1 -> 'B', ..., 25 -> 'Z'
            ans += (char)('A' + rem);
            
            // Shift the number right by one base-26 digit
            columnNumber /= 26;
        }
        
        // Reverse because we extracted the digits from right to left
        reverse(all(ans));
        
        return ans;
    }
};