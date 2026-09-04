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
PATTERN: Two Pointers (Single-Pass Interleave)
Time Complexity: O(N + M) | Space Complexity: O(N + M) for the result string
=======================================================================================
EXPLANATION OF LOGIC:
1. Initialize pointers `i` and `j` at the start of both strings.
2. The `while (i < n || j < m)` condition ensures the loop keeps firing until BOTH 
   strings are completely exhausted.
3. Inside, the safe `if (i < n)` and `if (j < m)` checks prevent out-of-bounds errors.
4. When one string runs out, its pointer simply stops advancing, and the remaining 
   iterations naturally append the rest of the longer string!
=======================================================================================
*/

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int n = sz(word1);
        int m = sz(word2);
        int i = 0, j = 0;
        
        string ans = "";
        
        // Loop runs as long as there are characters left in EITHER string
        while (i < n || j < m) {
            
            // Append from word1 if characters remain
            if (i < n) {
                ans.pb(word1[i]);
                i++;
            }
            
            // Append from word2 if characters remain
            if (j < m) {
                ans.pb(word2[j]);
                j++;
            }
        }
        
        return ans;
    }
};