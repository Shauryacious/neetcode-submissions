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
PATTERN: Floyd's Cycle Detection (Tortoise and Hare)
Time Complexity: O(N) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- PHASE 1 (Intersection): We initialize a `slow` pointer moving 1 step at a time, and 
  a `fast` pointer moving 2 steps at a time. Because a cycle exists, they are 
  mathematically guaranteed to collide.
- PHASE 2 (Cycle Entrance): Once they collide, we reset the `fast` pointer back to 
  the very beginning (index 0) and slow it down to move 1 step at a time.
- When they meet again, the meeting point is exactly the entrance to the cycle, which 
  corresponds to the duplicate number!
=======================================================================================
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        
        // Initialize both pointers at the start (index 0)
        // Since values are >= 1, index 0 is strictly outside the cycle and a perfect starting point
        int slow = nums[0];
        int fast = nums[nums[0]];
        
        // Phase 1: Find the intersection point inside the cycle
        while (slow != fast) {
            slow = nums[slow];           // moves 1 step
            fast = nums[nums[fast]];     // moves 2 steps
        }
        
        // Phase 2: Find the entrance to the cycle
        // Reset one of the pointers to the start
        fast = 0; 
        
        // Move both pointers at the exact same speed until they collide
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        
        // The collision point is the duplicate number
        return slow;
    }
};