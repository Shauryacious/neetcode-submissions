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
SOLUTION 1: Brute Force (Auxiliary Arrays)
Time Complexity: O(N) | Space Complexity: O(N)
=======================================================================================
EXPLANATION OF LOGIC:
1. We create a temporary array `ans`.
2. We first traverse `nums` and push all even elements to `ans`.
3. We traverse `nums` a second time and push all odd elements to `ans`.
4. Return the newly built array.
=======================================================================================
*/

class Solution1 {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int n = sz(nums);
        vector<int> ans;
        
        // Pass 1: Collect Evens
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 0) {
                ans.pb(nums[i]);
            }
        }
        
        // Pass 2: Collect Odds
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 != 0) {
                ans.pb(nums[i]);
            }
        }
        
        return ans;
    }
};

/*
=======================================================================================
SOLUTION 2: Optimal (Fast & Slow Pointers)
Time Complexity: O(N) | Space Complexity: O(1) In-place
=======================================================================================
EXPLANATION OF LOGIC:
1. Pointer `j` acts as the anchor, tracking where the next even number belongs.
2. Pointer `i` acts as the scout, checking every single element.
3. If `nums[i]` is even, we swap it to the anchor position `j`, and advance `j`.
4. If `nums[i]` is odd, we do nothing but let `i` advance. 
5. By the end, all even numbers have been swapped to the front, pushing odds back!
=======================================================================================
*/

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int n = sz(nums);
        
        int i = 0; // Fast pointer: Explores the array
        int j = 0; // Slow pointer: Tracks the target position for the next EVEN number
        
        while (i < n) {
            
            // If we find an even number, swap it to the front
            if (nums[i] % 2 == 0) {
                swap(nums[i], nums[j]);
                j++; // Advance the anchor since it is now filled
            }
            
            // Fast pointer ALWAYS moves forward
            i++;
        }
        
        return nums;
    }
};