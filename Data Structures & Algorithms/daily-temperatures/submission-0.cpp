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
SOLUTION 1: Brute Force (Nested Loops)
Time Complexity: O(N^2) | Space Complexity: O(1) auxiliary space (excluding output)
=======================================================================================
EXPLANATION:
- For every day `i`, we scan forward through subsequent days until we find a 
  temperature strictly greater than `temperatures[i]`.
- We record the distance `j - i` and break. If none is found, it remains 0.
=======================================================================================
*/

class Solution1 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = sz(temperatures);
        vector<int> ans(n, 0); // Default initialization to 0
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (temperatures[j] > temperatures[i]) {
                    ans[i] = j - i;
                    break;
                }
            }
        }
        
        return ans;
    }
};

/*
=======================================================================================
SOLUTION 2: Optimal Monotonic Stack (PPAP Pattern for Next Greater Element)
Time Complexity: O(N) | Space Complexity: O(N) for the stack
=======================================================================================
EXPLANATION & PPAP FLOW:
- Direction: Since this is a "Next" problem (Next Greater Element / NGE), we iterate 
  backwards from `n - 1` down to `0`.
- Stack Storage: We store **indices** instead of temperatures so we can compute distance.
- PPAP Flow:
  1. POP: Pop any elements from the stack whose temperature is less than or equal to 
     the current day's temperature (since they can never be a "next greater" day).
  2. ANS: If the stack is not empty, the top index represents the next warmer day. 
     The distance is `st.top() - i`.
  3. PUSH: Push the current index `i` onto the stack to act as a candidate for days further left.
=======================================================================================
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = sz(temperatures);
        stack<int> st; // Stores indices
        
        // Default initialization: 0 if no warmer day exists
        vector<int> ans(n, 0); 
        
        // Next Greater Element -> Iterate Backwards
        for (int i = n - 1; i >= 0; i--) {
            
            // POP -> PP
            // Jab tak stack top ki temperature <= current temperature hai, pop karte raho!
            while (!st.empty() && temperatures[st.top()] <= temperatures[i]) {
                st.pop();
            }
            
            // ANS -> A
            if (!st.empty()) {
                ans[i] = st.top() - i; // Distance to the next warmer day
            }
            
            // PUSH -> P
            st.push(i);
        }
        
        return ans;
    }
};