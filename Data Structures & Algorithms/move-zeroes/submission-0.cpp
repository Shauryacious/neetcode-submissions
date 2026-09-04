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
SOLUTION 1: Brute Force (Auxiliary Array)
Time Complexity: O(N) | Space Complexity: O(N) (Violates in-place constraint)
=======================================================================================
EXPLANATION OF LOGIC:
1. Create a temporary vector `temp`.
2. Traverse the original array. If an element is non-zero, push it to `temp`.
3. Overwrite the original array with the contents of `temp`.
4. Fill the remaining spots at the end of the original array with 0s.
=======================================================================================
*/

class Solution1 {
public:
    void moveZeroes(vector<int>& nums) {
        int n = sz(nums);
        vector<int> temp;
        
        // Collect all non-zero elements
        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                temp.pb(nums[i]);
            }
        }
        
        // Overwrite original array
        for (int i = 0; i < sz(temp); i++) {
            nums[i] = temp[i];
        }
        
        // Pad the rest with zeros
        for (int i = sz(temp); i < n; i++) {
            nums[i] = 0;
        }
    }
};

/*
=======================================================================================
SOLUTION 2: Optimal (Fast & Slow Pointers with while-loop)
Time Complexity: O(N) | Space Complexity: O(1) In-place
=======================================================================================
EXPLANATION OF LOGIC:
1. We maintain a slow pointer `j` which represents the destination index for the 
   next non-zero element.
2. We use a fast pointer `i` to explore the array.
3. The `while` loop drives `i` forward on every single iteration.
4. When `i` encounters a non-zero element, we swap it with the element at `j`, 
   and ONLY THEN do we advance the slow pointer `j`.
5. This naturally rolls all the zeros to the back of the array!
=======================================================================================
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = sz(nums);
        
        int i = 0; // Fast pointer: Explores the array
        int j = 0; // Slow pointer: Tracks the target position for the next non-zero
        
        while (i < n) {
            // When we find a non-zero element, swap it to the anchor position
            if (nums[i] != 0) {
                swap(nums[i], nums[j]);
                j++; // Advance the anchor since it is now filled
            }
            
            // Fast pointer ALWAYS moves forward to check the next element
            i++;
        }
    }
};