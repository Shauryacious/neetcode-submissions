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
PATTERN: Greedy + Two Pointers
Time Complexity: O(N log N + M log M) due to sorting | Space Complexity: O(1)
=======================================================================================
EXPLANATION OF LOGIC:
1. Sort both the greed factors (`g`) and cookie sizes (`s`) in ascending order.
2. Use pointer `i` for children, pointer `j` for cookies, and `cnt` to track success.
3. Iterate as long as we have both children and cookies left to check.
4. If the current cookie `s[j]` satisfies the current child `g[i]`, we assign it!
   We increment our explicit `cnt` and advance `i` to the next child.
5. Whether the cookie was used or was too small, we always advance `j` to the next cookie.
=======================================================================================
*/

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int n = sz(g);
        int m = sz(s);
        
        // Step 1: Sort to enable Greedy matching
        sort(all(g));
        sort(all(s));

        int i = 0;   // Pointer for children
        int j = 0;   // Pointer for cookies
        int cnt = 0; // Explicitly tracks satisfied children

        // Step 2: Traverse both arrays
        while (i < n && j < m) {
            
            // If the cookie is large enough for the current child
            if (s[j] >= g[i]) {
                cnt++; // The child is satisfied!
                i++;   // Move to the next child
            }
            
            // ALWAYS move to the next cookie 
            j++;
        }

        return cnt;
    }
};