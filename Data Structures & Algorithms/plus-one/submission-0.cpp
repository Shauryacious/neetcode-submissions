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
PATTERN: Array-Based Math (Schoolbook Addition)
Time Complexity: O(N) | Space Complexity: O(1) in-place modification
=======================================================================================
Explanation:
- We traverse the array from right to left (least significant to most significant).
- If the digit is < 9, we safely add 1 and return the array instantly, breaking the 
  loop. There are no cascading carries.
- If the digit is exactly 9, we set it to 0, and the loop naturally progresses to the 
  left, carrying the 1 over to the next iteration.
- If we finish the entire loop without returning, it means every single digit was a 9 
  (e.g., 999). The array is now filled with zeros (000). We just insert a 1 at the 
  very beginning to make it 1000.
=======================================================================================
*/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        
        // Start from the rightmost digit
        for (int i = n - 1; i >= 0; i--) {
            
            // If the digit is less than 9, just add 1 and we are completely done!
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            
            // If the digit is 9, it becomes 0, and we effectively "carry over" 1 
            // to the next loop iteration.
            digits[i] = 0;
        }
        
        // If we successfully exited the loop, it means ALL digits were 9.
        // Example: [9, 9] became [0, 0]. We must prepend a 1 to make it [1, 0, 0].
        digits.insert(digits.begin(), 1);
        
        return digits;
    }
};