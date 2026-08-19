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
#define INF 1e18
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
Time Complexity: O(log N) | Space Complexity: O(1) auxiliary
=======================================================================================
Explanation:
- We create a helper lambda `getNext` that extracts digits using modulo 10, squares 
  them, and returns the sum.
- `slow` acts as the tortoise, moving 1 step at a time.
- `fast` acts as the hare, moving 2 steps at a time.
- If the sequence drops to 1, the fast pointer will reach 1 first and just stay at 1.
- If there's a loop, `fast` will eventually wrap around the loop and collide directly 
  with `slow`.
- The loop terminates the moment `slow == fast`. We then just check if they collided 
  at the number 1!
=======================================================================================
*/

class Solution {
public:
    bool isHappy(int n) {
        
        // Helper function to calculate the sum of the squares of digits
        auto getNext = [&](int num) -> int {
            int total_sum = 0;
            while (num > 0) {
                int digit = num % 10;
                total_sum += digit * digit;
                num /= 10;
            }
            return total_sum;
        };

        // Initialize our Two Pointers
        int slow = n;
        int fast = getNext(n); // Fast starts one step ahead

        // Run until they collide
        while (fast != 1 && slow != fast) {
            
            slow = getNext(slow);                   // Moves 1 step
            fast = getNext(getNext(fast));          // Moves 2 steps
        }

        // If they broke out of the loop because fast hit 1, it's a happy number!
        return fast == 1;
    }
};