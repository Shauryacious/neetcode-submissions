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
PATTERN: Array State Tracking (Two-Way Sweep)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
EXPLANATION OF LOGIC:
1. Initialize an array of size N with all 1s (since every child needs at least 1 candy).
2. Sweep Left-to-Right: Ensure the condition is met comparing to the LEFT neighbor.
   If `ratings[i] > ratings[i-1]`, `candies[i] = candies[i-1] + 1`.
3. Sweep Right-to-Left: Ensure the condition is met comparing to the RIGHT neighbor.
   If `ratings[i] > ratings[i+1]`, we must ensure `candies[i] > candies[i+1]`. 
   To preserve the left-to-right rule, we update it to `max(candies[i], candies[i+1] + 1)`.
4. Sum up the `candies` array for the final answer.
=======================================================================================
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = sz(ratings);
        if (n == 0) return 0;
        
        // Give everyone 1 candy initially
        vector<int> candies(n, 1);
        
        // Pass 1: Left to Right
        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        
        // Pass 2: Right to Left
        for (int i = n - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i + 1]) {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }
        
        // Accumulate total candies safely using long long
        ll total_candies = 0;
        for (int c : candies) {
            total_candies += c;
        }
        
        return (int)total_candies;
    }
};