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
PATTERN: Stack (Last-In-First-Out Simulation)
Time Complexity: O(N) | Space Complexity: O(N) auxiliary stack space
=======================================================================================
EXPLANATION OF LOGIC:
1. Initialize an empty stack of strings to represent our folder hierarchy.
2. Iterate through each log.
3. If it's "../", we pop the top of the stack (if it's not already empty).
4. If it's "./", we ignore it.
5. Otherwise, it's a valid folder name, so we push it onto the stack.
6. The size of the stack at the end represents how many directories deep we are, 
   which is exactly how many "../" operations we need to return to the root.
=======================================================================================
*/

class Solution {
public:
    int minOperations(vector<string>& logs) {
        stack<string> st;
        
        for (auto log : logs) {
            if (log == "../") {
                // Go back one directory if we aren't already at the root
                if (!st.empty()) {
                    st.pop();
                }
            } 
            else if (log == "./") {
                // Stay in the current directory
                continue;
            } 
            else {
                // Dive into a new child directory
                st.push(log);
            }
        }
        
        // The remaining elements are the exact path depth
        return st.size();
    }
};