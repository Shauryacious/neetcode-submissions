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
SOLUTION 1: Brute Force (Using a Set)
Time Complexity: O(N log N) | Space Complexity: O(N) (Violates in-place constraint)
=======================================================================================
EXPLANATION OF LOGIC:
1. `std::set` automatically filters out duplicates and keeps elements sorted.
2. We iterate through the array and insert every element into the set.
3. We then iterate through the set and overwrite the beginning of the original array.
4. Return the size of the set, which represents the number of unique elements (k).
=======================================================================================
*/

class Solution1 {
public:
    int removeDuplicates(vector<int>& nums) {
        set<int> unique_elements;
        
        // Collect all unique elements
        for (auto& x : nums) {
            unique_elements.insert(x);
        }
        
        // Overwrite the original array
        int k = 0;
        for (auto& x : unique_elements) {
            nums[k] = x;
            k++;
        }
        
        return k;
    }
};

/*
=======================================================================================
SOLUTION 2: Optimal (Fast & Slow Pointers)
Time Complexity: O(N) | Space Complexity: O(1) In-place
=======================================================================================
EXPLANATION OF LOGIC:
1. The first element (index 0) is inherently unique. We start both pointers at index 1.
2. Fast pointer `i` explores the array. Slow pointer `j` tracks where to drop the 
   next unique element.
3. If `nums[i] != nums[i - 1]`, we've transitioned to a new unique number.
4. We copy `nums[i]` to `nums[j]`, then increment `j`.
5. At the end of the loop, `j` holds the exact count of unique elements!
=======================================================================================
*/

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = sz(nums);
        if (n == 0) return 0;
        
        int i = 1; // Fast pointer: Explores the array for new elements
        int j = 1; // Slow pointer: Tracks the placement index for the next unique element
        
        while (i < n) {
            // A number is unique if it differs from the one immediately preceding it
            if (nums[i] != nums[i - 1]) {
                nums[j] = nums[i];
                j++; // Advance the anchor
            }
            
            // Fast pointer ALWAYS moves forward
            i++;
        }
        
        return j; // 'j' represents the total count of unique elements placed
    }
};