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
PATTERN: Two Pointers & String Parsing
Time Complexity: O(M) where M is the length of abbr | Space Complexity: O(1)
=======================================================================================
EXPLANATION OF LOGIC:
1. `i` tracks our position in `word`, `j` tracks our position in `abbr`.
2. We walk through `abbr` checking character by character.
3. If it's a letter (`isalpha`), it must match `word[i]`. Both advance by 1.
4. If it's a digit:
   - Immediately check for leading '0'. If true, it's invalid.
   - Parse the contiguous digits to form the `jump` integer.
   - Advance the `word` pointer `i` by `jump`.
5. Finally, ensure both pointers hit the exact end of their strings. If `i` overshoots 
   or stops early, it returns false.
=======================================================================================
*/

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int i = 0, j = 0;
        int n = sz(word), m = sz(abbr);

        while (i < n && j < m) {
            
            // Case 1: We hit a letter
            if (isalpha(abbr[j])) {
                if (word[i] != abbr[j]) {
                    return false; // Mismatch found
                }
                i++;
                j++;
            } 
            // Case 2: We hit a number (abbreviation jump)
            else {
                // Rule: Leading zeros are strictly forbidden
                if (abbr[j] == '0') {
                    return false;
                }
                
                int jump = 0;
                // Parse the full number
                while (j < m && isdigit(abbr[j])) {
                    jump = jump * 10 + (abbr[j] - '0');
                    j++;
                }
                
                // Fast-forward the word pointer
                i += jump;
            }
        }

        // Both pointers must EXACTLY reach the end. 
        // If i > n, the jump was too large. If j < m, there are leftover abbreviation chars.
        return i == n && j == m;
    }
};