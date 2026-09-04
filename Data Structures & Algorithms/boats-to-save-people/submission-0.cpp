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
PATTERN: Greedy + Inward Two Pointers
Time Complexity: O(N log N) for sorting | Space Complexity: O(1) auxiliary space
=======================================================================================
EXPLANATION OF LOGIC:
1. Sort the array to easily access the lightest and heaviest individuals.
2. `left` points to the lightest person, `right` points to the heaviest.
3. Every iteration of the `while` loop dispatches exactly one boat (`boats++`).
4. If `people[left] + people[right] <= limit`, they pair up. Advance both pointers.
5. If they exceed the limit, the heavy person must ride alone. We only advance 
   the `right` pointer inward. The `left` pointer stays put, waiting to see if 
   the *next* heaviest person can pair with them.
=======================================================================================
*/

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        // Step 1: Sort the array
        sort(all(people));
        
        int left = 0;
        int right = sz(people) - 1;
        int boats = 0;
        
        // Step 2: Traverse from the outside in
        // We use <= because the final person must also be put in a boat
        while (left <= right) {
            
            // Explicitly extract weights for readability
            int lightest = people[left];
            int heaviest = people[right];
            
            // Check if they can share a boat
            if (lightest + heaviest <= limit) {
                // They fit! Both get on the boat.
                left++;
                right--;
            } 
            else {
                // Too heavy together! The heaviest person must go alone.
                // The lightest person stays behind for the next boat.
                right--;
            }
            
            // Regardless of whether 1 or 2 people got on, a boat departs
            boats++;
        }
        
        return boats;
    }
};