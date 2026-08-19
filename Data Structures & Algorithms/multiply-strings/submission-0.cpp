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
PATTERN: Schoolbook Multiplication with Index Mapping
Time Complexity: O(M * N) | Space Complexity: O(M + N) auxiliary array
=======================================================================================
Explanation:
- We handle the "0" edge case immediately to avoid returning things like "000".
- We create a `res` vector of size M + N to hold the digits.
- We iterate backwards through both strings.
- The product of `num1[i]` and `num2[j]` naturally maps to `res[i + j]` (for the carry) 
  and `res[i + j + 1]` (for the base digit).
- We add the sub-product to the existing value at `res[i + j + 1]`, split it using 
  modulo 10 and divide by 10, and propagate the carry to the left.
- Finally, we skip any leading zeros in the `res` array and build our final string!
=======================================================================================
*/

class Solution {
public:
    string multiply(string num1, string num2) {
        
        // Edge case: If either number is literally zero, the product is zero.
        if (num1 == "0" || num2 == "0") return "0";
        
        int n = num1.size();
        int m = num2.size();
        
        // The maximum possible length of the product is n + m
        vii res(n + m, 0);
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                
                // Multiply the two single digits
                int mul = (num1[i] - '0') * (num2[j] - '0');
                
                // Add the new product to whatever is already occupying the target slot
                int sum = mul + res[i + j + 1];
                
                // Place the ones-place digit in the current slot
                res[i + j + 1] = sum % 10;
                
                // Carry the tens-place digit over to the left slot
                res[i + j] += sum / 10;
            }
        }
        
        string ans = "";
        
        // Convert the result array back to a string, skipping any leading zeros
        for (int digit : res) {
            
            // We only start pushing characters once we hit a non-zero digit
            if (!(ans.empty() && digit == 0)) {
                ans.pb(digit + '0');
            }
        }
        
        return ans;
    }
};